visuConfigFileAdd_resourcesPath(char* dir)
{
  GList *element;

  if (!dir || !dir[0])
    return (GList*)0;

  element = g_list_find_custom(resourcesPath, (gconstpointer)dir,
			       compareStringsInGList);
  if (!element)
    {
      DBG_fprintf(stderr, "Visu ConfigFile: add a new resource directory"
		  " to the path :\n '%s'\n", dir);
      resourcesPath = g_list_insert(resourcesPath, (gpointer)dir, 1);
      return resourcesPath->next;
    }
  else
    return (GList*)element;
}
