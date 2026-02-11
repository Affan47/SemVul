jclass_class_new_from_buffer(const char* data)
{
	JavaClass* class_struct;
	const char* buf = data;

	if(data == NULL)
		return NULL;

	if (read_uint32(&buf) != JAVA_CLASS_MAGIC)
		return NULL;

	class_struct = (JavaClass*) malloc(sizeof(JavaClass));

	class_struct->minor_version = read_uint16(&buf);
	class_struct->major_version = read_uint16(&buf);

	class_struct->constant_pool = read_constant_pool(&buf);

	class_struct->access_flags = read_uint16(&buf);
	class_struct->constant_pool->this_class = read_uint16(&buf);
	class_struct->constant_pool->super_class = read_uint16(&buf);

	class_struct->interfaces_count = read_uint16(&buf);
	class_struct->interfaces = read_interfaces(&buf, class_struct->interfaces_count);

	class_struct->fields_count = read_uint16(&buf);
	class_struct->fields = read_fields(&buf, class_struct->fields_count);

	class_struct->methods_count = read_uint16(&buf);
	class_struct->methods = read_fields(&buf, class_struct->methods_count);

	class_struct->attributes_count = read_uint16(&buf);
	class_struct->attributes = read_attributes(&buf, class_struct->attributes_count);

	return class_struct;
}
