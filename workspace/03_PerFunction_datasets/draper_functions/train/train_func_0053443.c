imt_emit_ir (MonoImtBuilderEntry **sorted_array, int start, int end, GPtrArray *out_array)
{
	int count = end - start;
	int chunk_start = out_array->len;
	if (count < 4) {
		int i;
		for (i = start; i < end; ++i) {
			MonoIMTCheckItem *item = g_new0 (MonoIMTCheckItem, 1);
			item->key = sorted_array [i]->key;
			item->value = sorted_array [i]->value;
			item->has_target_code = sorted_array [i]->has_target_code;
			item->is_equals = TRUE;
			if (i < end - 1)
				item->check_target_idx = out_array->len + 1;
			else
				item->check_target_idx = 0;
			g_ptr_array_add (out_array, item);
		}
	} else {
		int middle = start + count / 2;
		MonoIMTCheckItem *item = g_new0 (MonoIMTCheckItem, 1);

		item->key = sorted_array [middle]->key;
		item->is_equals = FALSE;
		g_ptr_array_add (out_array, item);
		imt_emit_ir (sorted_array, start, middle, out_array);
		item->check_target_idx = imt_emit_ir (sorted_array, middle, end, out_array);
	}
	return chunk_start;
}
