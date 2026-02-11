load_exported_class(ARCHIVE *arch)
{

  char *buffer;
  int len;
  char *name;
  CLASS *class;
	CLASS **exported = NULL;
	int i;


  #if DEBUG_COMP
    fprintf(stderr, "load_exported_class: %s (component: %s)\n", arch->name, COMPONENT_current ? COMPONENT_current->name : "?");
  #endif

	if (!FILE_exist(".list"))
		return;

  STREAM_load(".list", &buffer, &len);

  buffer[len - 1] = 0;

  #if DEBUG_COMP
    fprintf(stderr, ".list file:\n-----------\n\n%s\n----------\n\n", buffer);
  #endif

	ARRAY_create(&exported);

  name = strtok(buffer, "\n");
  while (name)
  {
    #if DEBUG_COMP
      fprintf(stderr, "Check %s global\n", name);
    #endif

    CLASS_check_global(name);

		len = strlen(name);
		if (len > 2 && name[len - 1] == '?')
		{
			name[len - 1] = 0;
			if (!CLASS_look_global(name, strlen(name)))
				class = CLASS_find_global(name);
			else
				class = NULL;
		}
		else
    	class = CLASS_find_global(name);

		if (class)
		{
			class->component = COMPONENT_current;
			*((CLASS **)ARRAY_add(&exported)) = class;
		}

    name = strtok(NULL, "\n");
  }

	for (i = 0; i < ARRAY_count(exported); i++)
		CLASS_load_without_init(exported[i]);

	ARRAY_delete(&exported);
  FREE(&buffer, "load_exported_class");
}
