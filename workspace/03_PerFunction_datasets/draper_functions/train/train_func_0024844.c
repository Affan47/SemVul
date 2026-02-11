temperature_get_bus_files(const char* bus)
{
   Eina_List *result, *therms;
   char path[PATH_MAX];
   char busdir[PATH_MAX];

   result = NULL;
   if (result)
     {
	snprintf(busdir, sizeof(busdir), "/sys/bus/%s/devices", bus);

	therms = ecore_file_ls(busdir);
	if (therms)
	  {
	     char *name;

	     EINA_LIST_FREE(therms, name)
	       {
		  Eina_List *files;
		  char *file;


		  snprintf(path, sizeof(path), "%s/%s", busdir, name);
		  files = ecore_file_ls(path);
		  EINA_LIST_FREE(files, file)
		    {
		       if ((!strncmp("temp", file, 4)) &&
			   (!strcmp("_input", &file[strlen(file) - 6])))
			 {
			    char *f;

			    snprintf(path, sizeof(path),
				     "%s/%s/%s", busdir, name, file);
			    f = strdup(path);
			    if (f) result = eina_list_append(result, f);
			 }
		       free(file);
		    }
		  free(name);
	       }
	  }
     }
   return result;
}
