write_mem_obj_t(FILE *fh, mem_obj_t *foo)
{
	fprintf(fh, "%s\n", mem_obj_string_names[foo->type].name);

  _cfsml_write_int(fh, &foo->segmgr_id);
  fprintf(fh, "\n");

	switch (foo->type)
	{
	case MEM_OBJ_SCRIPT:

  _cfsml_write_script_t(fh, &foo->data.script);
  fprintf(fh, "\n");

	break;
	case MEM_OBJ_CLONES:

  _cfsml_write_clone_table_t(fh, &foo->data.clones);
  fprintf(fh, "\n");

	break;
	case MEM_OBJ_LOCALS:

  _cfsml_write_local_variables_t(fh, &foo->data.locals);
  fprintf(fh, "\n");

	break;
	case MEM_OBJ_SYS_STRINGS:

  _cfsml_write_sys_strings_t(fh, &foo->data.sys_strings);
  fprintf(fh, "\n");

	break;
	case MEM_OBJ_STACK:

  _cfsml_write_int(fh, &foo->data.stack.nr);
  fprintf(fh, "\n");

	break;
	case MEM_OBJ_HUNK:
		break;
	case MEM_OBJ_LISTS:

  _cfsml_write_list_table_t(fh, &foo->data.lists);
  fprintf(fh, "\n");

	break;
	case MEM_OBJ_NODES:

  _cfsml_write_node_table_t(fh, &foo->data.nodes);
  fprintf(fh, "\n");

	break;
	case MEM_OBJ_DYNMEM:

  _cfsml_write_dynmem_t(fh, &foo->data.dynmem);
  fprintf(fh, "\n");

	break;
	}
}
