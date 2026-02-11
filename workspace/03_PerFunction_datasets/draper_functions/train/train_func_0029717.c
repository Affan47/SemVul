vm_method_init(struct vm_method *vmm,
	struct vm_class *vmc, unsigned int method_index)
{
	const struct cafebabe_class *class = vmc->class;
	const struct cafebabe_method_info *method
		= &class->methods[method_index];

	vmm->class = vmc;
	vmm->method_index = method_index;
	vmm->method = method;
	vmm->flags = 0;
	vmm->annotation_initialized = false;

	const struct cafebabe_constant_info_utf8 *name;
	if (cafebabe_class_constant_get_utf8(class, method->name_index, &name))
		return -1;

	vmm->name = strndup((char *) name->bytes, name->length);
	if (!vmm->name)
		return -1;

	const struct cafebabe_constant_info_utf8 *type;
	if (cafebabe_class_constant_get_utf8(class, method->descriptor_index, &type))
		goto error_free_name;

	vmm->type = strndup((char *) type->bytes, type->length);
	if (!vmm->type)
		goto error_free_name;

	if (vm_method_do_init(vmm))
		goto error_free_type;


	if (vm_method_is_native(vmm) || vm_method_is_abstract(vmm)) {
		init_abstract_method(vmm);
		return 0;
	}

	unsigned int code_index = 0;
	if (cafebabe_attribute_array_get(&method->attributes, "Code", class, &code_index))
		goto error_free_type;


	unsigned int code_index2 = code_index + 1;
	if (!cafebabe_attribute_array_get(&method->attributes, "Code", class, &code_index2))
		goto error_free_type;

	const struct cafebabe_attribute_info *attribute
		= &method->attributes.array[code_index];

	struct cafebabe_stream stream;
	cafebabe_stream_open_buffer(&stream,
		attribute->info, attribute->attribute_length);

	if (cafebabe_code_attribute_init(&vmm->code_attribute, &stream))
		goto error_free_type;

	cafebabe_stream_close_buffer(&stream);

	if (cafebabe_read_exceptions_attribute(class, &method->attributes, &vmm->exceptions_attribute))
		goto error_free_type;

	if (cafebabe_read_line_number_table_attribute(class, &vmm->code_attribute.attributes, &vmm->line_number_table_attribute))
		goto error_free_type;

	return 0;

error_free_type:
	free(vmm->type);
error_free_name:
	free(vmm->name);

	return -1;
}
