cfg_add_key(ConfigFile *cf, char *key, char *value)
{
	int result = 0;
	int strsize = 0;
	int i;

	if (cfg_get_key_value(*cf, key) != NULL)
	{
		for (i = 0; i < cf->lastkey; i++)
			if (strncmp(key, cf->key[i], 127) == 0)
			{
				free(cf->key[i]);
				free(cf->value[i]);


				strsize = (strlen(key) < 127 ? strlen(key) : 126) + 1;
				cf->key[i] = (char*)malloc(strsize * sizeof(char));
				sprintf(cf->key[i], "%s", key);

				strsize = (strlen(key) < 127 ? strlen(value) : 126) + 1;
				cf->value[i] = (char*)malloc(strsize * sizeof(char));
				sprintf(cf->value[i], "%s", value);
				break;
			}
	}
	else if (cf->lastkey < MAXKEYS)
	{
		strsize = (strlen(key) < 127 ? strlen(key) : 126) + 1;
		cf->key[cf->lastkey] = (char*)malloc(strsize * sizeof(char));
		sprintf(cf->key[cf->lastkey], "%s", key);

		strsize = (strlen(key) < 127 ? strlen(value) : 126) + 1;
		cf->value[cf->lastkey] = (char*)malloc(strsize * sizeof(char));
		sprintf(cf->value[cf->lastkey], "%s", value);

		(cf->lastkey)++;
	}
	else
		result = -1;
	return result;
}
