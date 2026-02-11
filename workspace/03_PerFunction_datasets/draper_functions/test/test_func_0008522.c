_get_class_filename(const char* class_name,
	const ClassPath *classpath)
{
	const ClassPath *path;
	char* class_filename;
	char* class_unixfilename;
	char* absolute_class_filename = NULL;
	int path_len;
	FILE *file_ptr;

	if((strlen(class_name) > 6) && !strcmp(".class", &class_name[strlen(class_name) - 6]))
	{
		class_filename = strdup(class_name);
		class_unixfilename = strdup(class_name);
	}
	else
	{
		class_filename = jclass_classname_to_filename(class_name, SYSTEM_PATH_SLASH);
		class_unixfilename = jclass_classname_to_filename(class_name, '/');
	}

	foreach_in_classpath(path, classpath) {
		path_len = strlen(path->path);

		if ((path_len > 4) && !strcmp(&path->path[path_len - 4], ".jar"))
		{
			if(isin_jar(path->path, class_unixfilename))
			{
				absolute_class_filename = strdup(path->path);
				break;
			}
		}
		else
		{
			absolute_class_filename = (char*) malloc(path_len + strlen(class_filename) + 2);
			strcpy(absolute_class_filename, path->path);
			absolute_class_filename[path_len] = SYSTEM_PATH_SLASH;
			absolute_class_filename[path_len + 1] = '\0';
			strcat(absolute_class_filename, class_filename);

			file_ptr = my_open(absolute_class_filename,"rb");
			if (file_ptr) {
				fclose(file_ptr);
				break;
			}
			free(absolute_class_filename);

		}
	}

	return absolute_class_filename;
}
