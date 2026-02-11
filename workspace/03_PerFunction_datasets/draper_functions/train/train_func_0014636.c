emitusage(void)
{
	int i;

	fprintf(stderr, "[");
	for(i=0; i<FORMTABSIZE; ) {
		fprintf(stderr, "%s", formtab[i].name);
		if( ++i < FORMTABSIZE)
			fprintf(stderr, "|");
	}
	fprintf(stderr, "]");
}
