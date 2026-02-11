count_seqset_entities(FILE *fptr,ss_type P, long nsize[])
{
        long i=0,j,length,c;

	P->max_leng = 0; P->min_leng = 1000000;
	while((c=fgetc(fptr))!=EOF){ if(c=='>') break; }
        for(i=1,length=0;c!=EOF;length=0,i++) {
		if(c=='>') while((c=fgetc(fptr))!=EOF){ if(c=='\n') break; }
		while(c!='>') {
		   if(isalpha(c)) length++;
		   else if(!isspace(c)) {
			fprintf(stderr,"seq %ld: illegal character -> %c",i, (char)c);
			for(j=0; (c=fgetc(fptr)) != EOF; j++) {
				if(c == '\n') break;
				fprintf(stderr,"%c",(char)c);
				if(j > 10 || isspace(c)) break;
			}
			fprintf(stderr,"\n");
			seqset_error("input file error - fatal.");
		   }
           	   if((c=fgetc(fptr))==EOF) break;
	     	}
		if(i >= MAX_NUMBER_SEQS)
		   seqset_error("too many sequences; reset MAX_NUMBER_SEQS");
	   	P->max_leng = tMAX(long,P->max_leng,length);
		P->min_leng = tMIN(long,P->min_leng,length);
		nsize[i] = length;
	}
	i--;
        return i;
}
