emit_got_info (MonoAotCompile *acfg)
{
	char symbol [256];
	int i, first_plt_got_patch, buf_size;
	guint8 *p, *buf;
	guint32 *got_info_offsets;


	acfg->plt_got_offset_base = acfg->got_offset;
	first_plt_got_patch = acfg->got_patches->len;
	for (i = 1; i < acfg->plt_offset; ++i) {
		MonoPltEntry *plt_entry = g_hash_table_lookup (acfg->plt_offset_to_entry, GUINT_TO_POINTER (i));

		g_ptr_array_add (acfg->got_patches, plt_entry->ji);

		acfg->stats.got_slot_types [plt_entry->ji->type] ++;
	}

	acfg->got_offset += acfg->plt_offset;


	buf_size = acfg->got_patches->len * 128;
	p = buf = mono_mempool_alloc (acfg->mempool, buf_size);
	got_info_offsets = mono_mempool_alloc (acfg->mempool, acfg->got_patches->len * sizeof (guint32));
	acfg->plt_got_info_offsets = mono_mempool_alloc (acfg->mempool, acfg->plt_offset * sizeof (guint32));

	if (acfg->plt_offset)
		acfg->plt_got_info_offsets [0] = 0;
	for (i = 0; i < acfg->got_patches->len; ++i) {
		MonoJumpInfo *ji = g_ptr_array_index (acfg->got_patches, i);
		guint8 *p2;

		p = buf;

		encode_value (ji->type, p, &p);
		p2 = p;
		encode_patch (acfg, ji, p, &p);
		acfg->stats.got_slot_info_sizes [ji->type] += p - p2;
		g_assert (p - buf <= buf_size);
		got_info_offsets [i] = add_to_blob (acfg, buf, p - buf);

		if (i >= first_plt_got_patch)
			acfg->plt_got_info_offsets [i - first_plt_got_patch + 1] = got_info_offsets [i];
		acfg->stats.got_info_size += p - buf;
	}


	sprintf (symbol, "got_info_offsets");
	emit_section_change (acfg, RODATA_SECT, 1);
	emit_alignment (acfg, 8);
	emit_label (acfg, symbol);


	acfg->stats.offsets_size += emit_offset_table (acfg, first_plt_got_patch, 10, (gint32*)got_info_offsets);
}
