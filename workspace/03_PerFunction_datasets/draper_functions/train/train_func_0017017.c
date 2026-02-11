COMPONENT_create(const char *name)
{
  COMPONENT *comp;
  char *path = NULL;
  bool can_archive;
	bool library = FALSE;
	bool same_name_as_project = FALSE;

	if (*name == '/')
	{
		library = TRUE;
		path = (char *)name;
		name = FILE_get_name(name);
	}

  comp = COMPONENT_find(name);
  if (comp)
    return comp;

  ALLOC_ZERO(&comp, sizeof(COMPONENT), "COMPONENT_create");

  comp->class = CLASS_Component;
  comp->ref = 1;

  comp->name = STRING_new_zero(name);

	if (library)
	{
		comp->archive = ARCHIVE_create(name, path);
		comp->user = TRUE;
	}
	else
	{


		if (PROJECT_name)
			same_name_as_project = strcmp(name, PROJECT_name) == 0;

		can_archive = !same_name_as_project;


		path = FILE_buffer();
		sprintf(path, LIB_PATTERN, COMPONENT_path, name);

		if (FILE_exist(path))
			comp->library = LIBRARY_create(name);

		if (can_archive)
		{
			path = FILE_buffer();
			sprintf(path, ARCH_PATTERN, COMPONENT_path, name);

			if (FILE_exist(path))
				comp->archive = ARCHIVE_create(name, NULL);
		}
	}

  LIST_insert(&_component_list, comp, &comp->list);
  COMPONENT_count++;

  if (!comp->library && !comp->archive && !same_name_as_project)
	{
		COMPONENT_delete(comp);
		THROW(E_LIBRARY, name, "cannot find component");
	}

  return comp;
}
