IsPmiKey(char * key) {
	char strh[5];

	if (pmi_debug)
		fprintf(stderr, "In: IsPmiKey \n");

	strncpy(strh, key, 4);
	strh[4]='\0';
 	if (!strcmp(strh, "PMI_") && (strlen(key) > 4)) {
		return 1;
	}


	return 0;
}
