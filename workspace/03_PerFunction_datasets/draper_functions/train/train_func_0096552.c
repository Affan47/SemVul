cafebabe_code_attribute_deinit(struct cafebabe_code_attribute *a)
{
	free(a->exception_table);

	for (uint16_t i = 0; i < a->attributes.count; ++i)
		cafebabe_attribute_info_deinit(&a->attributes.array[i]);
	free(a->attributes.array);
}
