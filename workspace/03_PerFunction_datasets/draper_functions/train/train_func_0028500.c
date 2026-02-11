driver_bind_module(Driver *driver)
{
	int i;
	int missing_symbols = 0;

	debug(RPT_DEBUG, "%s(driver=[%.40s])", __FUNCTION__, driver->name);


	driver->module_handle = dlopen(driver->filename, RTLD_NOW);
	if (driver->module_handle == NULL) {
		report(RPT_ERR, "Could not open driver module %.40s: %s",
			driver->filename, dlerror());
		return -1;
	}


	for (i = 0; driver_symbols[i].name != NULL; i++) {
		void (**p)();

		p = (void(**)()) ((size_t)driver + (driver_symbols[i].offset));
		*p = NULL;


		if (driver->symbol_prefix != NULL) {
			char *s = malloc(strlen(*(driver->symbol_prefix)) + strlen(driver_symbols[i].name) + 1);
			strcpy(s, *(driver->symbol_prefix));
			strcat(s, driver_symbols[i].name);
			debug(RPT_DEBUG, "%s: finding symbol: %s", __FUNCTION__, s);
			*p = dlsym(driver->module_handle, s);
			free(s);
		}

		if (*p == NULL) {
			debug(RPT_DEBUG, "%s: finding symbol: %s", __FUNCTION__, driver_symbols[i].name);
			*p = dlsym(driver->module_handle, driver_symbols[i].name);
		}

		if (*p != NULL) {
			debug(RPT_DEBUG, "%s: found symbol at: %p", __FUNCTION__, *p);
		}
		else {

			if (driver_symbols[i].required) {
				report(RPT_ERR, "Driver [%.40s] does not have required symbol: %s",
					driver->name, driver_symbols[i].name);
				missing_symbols++;
			}
		}
	}


	if (missing_symbols > 0) {
  		report(RPT_ERR, "Driver [%.40s]  misses %d required symbols",
			driver->name, missing_symbols);
		dlclose(driver->module_handle);
		return -1;
	}


	driver->config_get_bool		= config_get_bool;
	driver->config_get_int		= config_get_int;
	driver->config_get_float	= config_get_float;
	driver->config_get_string	= config_get_string;
	driver->config_has_section	= config_has_section;
	driver->config_has_key		= config_has_key;


	driver->report			= report;


	driver->store_private_ptr	= driver_store_private_ptr;


	driver->request_display_width	= request_display_width;
	driver->request_display_height	= request_display_height;

	return 0;
}
