a_exec(char * opt[]) {
	int i;

	if(opt)
		for(i=0; opt[i]; i++)
			if(opt[i]) spawn(opt[i]);
	return 0;
}
