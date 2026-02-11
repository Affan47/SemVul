jclass_cp_new(const char* filename, const ClassPath *classpath)
{
	ConstantPool* new_cp = NULL;
	FILE* classfile;
	ClassFile* class_file_info;
	int is_filename;

	if(filename == NULL)
		return NULL;

	is_filename = (strlen(filename) > 6) && !strcmp(".class", &filename[strlen(filename) - 6]);

	if(!is_filename)
	{
		class_file_info = jclass_classloader_get_class_file(filename, classpath);

		if(class_file_info->data != NULL)
		{
			new_cp = jclass_cp_new_from_buffer(class_file_info->data);
			free(class_file_info->data);
		}
		else if(class_file_info->file_ptr != NULL)
		{
			new_cp = jclass_cp_new_from_file(class_file_info->file_ptr);
		}
		else
			new_cp = NULL;

		free(class_file_info);
	}
	else
	{
		classfile = fopen(filename, "rb");
		new_cp = jclass_cp_new_from_file(classfile);
	}

	return new_cp;
}
