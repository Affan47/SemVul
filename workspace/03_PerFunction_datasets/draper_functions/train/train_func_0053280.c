loadConfigFile(const char *fileName)
{
	char *sharedLib, *kernMod, *modOptions, *modType, *oid, *next;
	char buffer[BUFSIZ], *oidStr;
	FILE *confFile;

	if ((confFile = fopen(fileName, "r")) == NULL) {
		return;
	}

	(void) memset(buffer, 0, sizeof (buffer));
	while (fgets(buffer, BUFSIZ, confFile) != NULL) {


		if (*buffer == '#')
			continue;


		oidStr = buffer;
		oid = delimit_ws(oidStr);
		if (*oid == '\0')
			continue;
		sharedLib = delimit_ws(oid);
		if (*sharedLib == '\0')
			continue;
		next = delimit_ws(sharedLib);


		if (*next != '\0' && *next != '[' && *next != '<') {
			kernMod = next;
			next = delimit_ws(kernMod);
		} else {
			kernMod = NULL;
		}


		if (*next == '[') {
			modOptions = next + 1;
			next = delimit(modOptions, ']');
		} else {
			modOptions = NULL;
		}


		if (*next == '<') {
			modType = next + 1;
			(void)delimit(modType, '>');
		} else {
			modType = NULL;
		}

		addConfigEntry(oidStr, oid, sharedLib, kernMod, modOptions,
			       modType);
	}
	(void) fclose(confFile);
}
