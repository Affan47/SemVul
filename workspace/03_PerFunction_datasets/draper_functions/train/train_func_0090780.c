a_print(char * opt[]) {
	int i;

	if(opt)
		for(i=0; opt[i]; i++)
			puts(opt[i]);
	return 0;
}
