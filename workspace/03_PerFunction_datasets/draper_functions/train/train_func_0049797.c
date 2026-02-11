cafebabe_field_info_deinit(struct cafebabe_field_info *f)
{
	for (uint16_t i = 0; i < f->attributes.count; ++i)
		cafebabe_attribute_info_deinit(&f->attributes.array[i]);
	free(f->attributes.array);
}
