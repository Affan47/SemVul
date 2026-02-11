cafebabe_class_get_method(const struct cafebabe_class *c,
	const char *name, const char *descriptor,
	unsigned int *r)
{
	for (uint16_t i = 0; i < c->methods_count; ++i) {
		const struct cafebabe_constant_info_utf8 *method_name;
		if (cafebabe_class_constant_get_utf8(c,
			c->methods[i].name_index, &method_name))
		{
			return 1;
		}

		if (cafebabe_constant_info_utf8_compare(method_name, name))
			continue;

		const struct cafebabe_constant_info_utf8 *method_descriptor;
		if (cafebabe_class_constant_get_utf8(c,
			c->methods[i].descriptor_index, &method_descriptor))
		{
			return 1;
		}

		if (cafebabe_constant_info_utf8_compare(
			method_descriptor, descriptor))
		{
			continue;
		}

		*r = i;
		return 0;
	}


	return 1;
}
