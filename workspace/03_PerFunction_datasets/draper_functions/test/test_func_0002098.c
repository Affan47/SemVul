php_binary_init(TSRMLS_D)
{
	char *binary_location;
#ifdef PHP_WIN32
	binary_location = (char *)malloc(MAXPATHLEN);
	if (GetModuleFileName(0, binary_location, MAXPATHLEN) == 0) {
		free(binary_location);
		PG(php_binary) = NULL;
	}
#else
	if (sapi_module.executable_location) {
		binary_location = (char *)malloc(MAXPATHLEN);
		if (!strchr(sapi_module.executable_location, '/')) {
			char *envpath, *path;
			int found = 0;

			if ((envpath = getenv("PATH")) != NULL) {
				char *search_dir, search_path[MAXPATHLEN];
				char *last = NULL;

				path = estrdup(envpath);
				search_dir = php_strtok_r(path, ":", &last);

				while (search_dir) {
					snprintf(search_path, MAXPATHLEN, "%s/%s", search_dir, sapi_module.executable_location);
					if (VCWD_REALPATH(search_path, binary_location) && !VCWD_ACCESS(binary_location, X_OK)) {
						found = 1;
						break;
					}
					search_dir = php_strtok_r(NULL, ":", &last);
				}
				efree(path);
			}
			if (!found) {
				free(binary_location);
				binary_location = NULL;
			}
		} else if (!VCWD_REALPATH(sapi_module.executable_location, binary_location) || VCWD_ACCESS(binary_location, X_OK)) {
			free(binary_location);
			binary_location = NULL;
		}
	} else {
		binary_location = NULL;
	}
#endif
	PG(php_binary) = binary_location;
}
