jclass_cp_get_method_signature(const ConstantPool* constant_pool,
	uint16_t index, int return_type)
{
	int name_index;
	int type_index;
	int name_and_type_index;
	int class_name_index;
	int string_size;
	char* full_method_name;
	char* class_name;
	char* method_name;
	char* descriptor;
	char* parameters;
	char* type;
	ConstantPoolEntry* cpool;

	if(index > constant_pool->count)
		return NULL;

	cpool = constant_pool->entries;
	full_method_name = NULL;

	if(cpool[index].tag == CONSTANT_Empty)
		return NULL;

	if ((cpool[index].tag == CONSTANT_Methodref) ||
		(cpool[index].tag == CONSTANT_InterfaceMethodref) ||
		(cpool[index].tag == CONSTANT_Fieldref)
		)
	{
		class_name_index = cpool[index].info.ref.class_index;

		class_name = jclass_cp_get_class_name(constant_pool, class_name_index, 0);

		name_and_type_index = cpool[index].info.ref.name_and_type_index;
		name_index = cpool[name_and_type_index].info.nameandtype.name_index;
		type_index = cpool[name_and_type_index].info.nameandtype.descriptor_index;

		method_name = jclass_utf8_to_string(
					cpool[name_index].info.utf8->contents,
					cpool[name_index].info.utf8->length);

		if(!strcmp(method_name,"<init>"))
		{
			free(method_name);
			method_name = NULL;
		}

		descriptor = jclass_utf8_to_string(
						cpool[type_index].info.utf8->contents,
						cpool[type_index].info.utf8->length);

		parameters = jclass_descriptor_get_parameters(descriptor);
		type = jclass_descriptor_get_type(descriptor);
		free(descriptor);

		if(method_name == NULL)
			string_size = 0;
		else
			string_size = strlen(type) + strlen(method_name) + 2;

		string_size += strlen(class_name) + strlen(parameters) + 1;
		full_method_name = (char*) malloc(sizeof(char) * string_size);

		if(method_name != NULL)
		{
			if(return_type)
			{
				strcpy(full_method_name, type);
				strcat(full_method_name, " ");
			}
			else
				full_method_name[0] = '\0';
		}
		else
			full_method_name[0] = '\0';

		strcat(full_method_name, class_name);

		if(method_name != NULL)
		{
			strcat(full_method_name, ".");
			strcat(full_method_name, method_name);
			free(method_name);
		}
		strcat(full_method_name, parameters);

		free(type);
		free(class_name);
		free(parameters);
	}

	return full_method_name;
}
