compile_dictlist_end(FILE *f_out)
{

	int hash;
	int length;
	char *p;

	if(f_log != NULL)
	{
#ifdef OUTPUT_FORMAT
		for(hash=0; hash<N_HASH_DICT; hash++)
		{
			fprintf(f_log,"%8d",hash_counts[hash]);
			if((hash & 7) == 7)
				fputc('\n',f_log);
		}
		fflush(f_log);
#endif
	}

	for(hash=0; hash<N_HASH_DICT; hash++)
	{
		p = hash_chains[hash];
		hash_counts[hash] = (int)ftell(f_out);

		while(p != NULL)
		{
			length = *(p+sizeof(char *));
			fwrite(p+sizeof(char *),length,1,f_out);
			memcpy(&p,p,sizeof(char *));
		}
		fputc(0,f_out);
	}
}
