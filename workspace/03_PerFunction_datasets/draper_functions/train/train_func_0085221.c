parse_name(Player *p, char *input) {
	char	*ptr;
	char	*ptr2;
	int	i;
	int	total = 0;

	p->name = NULL;


	for(ptr = input; isblank(*ptr); ptr++);
	if(*ptr == '\0') return -1;


	for(ptr2 = ptr; !isblank(*ptr2) && *ptr2 != '\0'; ptr2++);
	if(*ptr2 == '\0') return -1;


	p->name = strdup2(ptr, ptr2 - ptr);


	for(i = 0; i < battlefields; i++) {

		for(ptr = ptr2; isblank(*ptr); ptr++);
		if(*ptr == '\0') return -1;


		for(ptr2 = ptr; !isblank(*ptr2) && *ptr2 != '\0'; ptr2++);
		if(*ptr2 == '\0' && i != (battlefields - 1)) return -1;


		p->soldiers[i] = strtol(ptr, NULL, 0);


		total += p->soldiers[i];
		if(total > soldiers)
			fprintf(stderr, "Using more than %d soldiers in '%s'!\n", soldiers,
			        input);
	}


	if(total < soldiers)
		fprintf(stderr, "Using less than %d soldiers in '%s'!\n", soldiers, input);


	for(ptr = ptr2; isblank(*ptr); ptr++);
	if(*ptr != '\0') {
		fprintf(stderr, "Using more than %d battlefields in '%s'!\n", battlefields,
		        input);
	}

	return 0;
}
