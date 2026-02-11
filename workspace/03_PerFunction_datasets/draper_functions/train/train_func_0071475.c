parse_subnets (char *filename, hlist_t **ha) {
	FILE *fin = NULL;
	char *str;
	char *key, *val;
	char buff[512];

	fin = fopen (filename, "r");
	if (NULL==fin)  return errno;

        while ( (str=fgets(buff, 512, fin)) ) {

	get_two_tok(str, &key, &val);


	if (!strcmpi("subnet",key)) preload_subnets(val,ha);

	}

	fclose(fin);

	return 1;

}
