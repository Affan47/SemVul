jclass_class_new_from_file(FILE* classfile)
{
	JavaClass* class_struct;

	if (classfile == NULL)
		return NULL;

	if (fread_uint32(classfile) != JAVA_CLASS_MAGIC)
	{
		fclose(classfile);
		return NULL;
	}

	class_struct = (JavaClass*) malloc(sizeof(JavaClass));

	class_struct->minor_version = fread_uint16(classfile);
	class_struct->major_version = fread_uint16(classfile);

	class_struct->constant_pool = fread_constant_pool(classfile);

	class_struct->access_flags = fread_uint16(classfile);
	class_struct->constant_pool->this_class = fread_uint16(classfile);
	class_struct->constant_pool->super_class = fread_uint16(classfile);
	class_struct->interfaces_count = fread_uint16(classfile);

	class_struct->interfaces = fread_interfaces(classfile, class_struct->interfaces_count);
	class_struct->fields_count = fread_uint16(classfile);
	class_struct->fields = fread_fields(classfile, class_struct->fields_count);

	class_struct->methods_count = fread_uint16(classfile);
	class_struct->methods = fread_fields(classfile, class_struct->methods_count);
	class_struct->attributes_count = fread_uint16(classfile);
	class_struct->attributes = fread_attributes(classfile, class_struct->attributes_count);
	fclose(classfile);
	return class_struct;
}
