lt_finalize_dictionary(struct lt_trace *lt)
{
int i;

lt->sorted_dict = calloc(lt->num_dict_entries, sizeof(dslxt_Tree *));

lt->dictionary_offset=lt->position;

lt_emit_u32(lt, lt->num_dict_entries);
lt_emit_u32(lt, lt->dict_string_mem_required - lt->num_dict_entries);
lt_emit_u32(lt, lt->dict16_offset);
lt_emit_u32(lt, lt->dict24_offset);
lt_emit_u32(lt, lt->dict32_offset);
lt_emit_u32(lt, lt->mindictwidth);
fflush(lt->handle);

#if 0
fprintf(stderr, "*** dictionary_offset = %08x\n", lt->dictionary_offset);
fprintf(stderr, "*** num_dict_entries = %d\n", lt->num_dict_entries);
#endif

lt->zdictionary_size = lt->position;
lt->zhandle = gzdopen(dup(fileno(lt->handle)), "wb9");

lt_recurse_dictionary(lt, lt->dict);
qsort((void *)lt->sorted_dict, lt->num_dict_entries, sizeof(struct dsTree **), lt_dictval_compare);

for(i=0;i<lt->num_dict_entries;i++)
	{
	dslxt_Tree *ds = lt->sorted_dict[i];

	lt_emit_stringz(lt, ds->item+1);
	}

gzclose(lt->zhandle);
fseeko(lt->handle, 0L, SEEK_END);
lt->position=ftello(lt->handle);
lt->zdictionary_size = lt->position - lt->zdictionary_size;

free(lt->sorted_dict); lt->sorted_dict = NULL;

lt_recurse_dictionary_free(lt, lt->dict);
lt->dict = NULL;
}
