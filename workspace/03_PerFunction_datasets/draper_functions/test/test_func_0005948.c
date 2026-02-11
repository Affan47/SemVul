readseqs(int first_seq)
{
	char line[FILENAMELEN+1];
	static char seq1[MAXLEN+2],sname1[MAXNAMES+1],title[MAXTITLES+1];
	int i,j,no_seqs;
	static int l1;
	static Boolean dnaflag1;

	if(usemenu)
		getstr("Enter the name of the sequence file",line);
	else
		strcpy(line,seqname);
	if(*line == EOS) return -1;

	if((fin=fopen(line,"r"))==NULL) {
		error("Could not open sequence file %s",line);
		return -1;
	}
	strcpy(seqname,line);
	no_seqs=0;
	check_infile(&no_seqs);
	printf("\nSequence format is %s\n",formatNames[seqFormat]);
	if(no_seqs == 0)
		return 0;

	if((no_seqs + first_seq -1) > MAXN) {
		error("Too many sequences. Maximum is %d",MAXN);
		return 0;
	}

	for(i=first_seq;i<=first_seq+no_seqs-1;++i) {
		get_seq(sname1,seq1,&l1,title);
		seqlen_array[i]=l1;
		strcpy(names[i],sname1);
		strcpy(titles[i],title);

		if(!explicit_dnaflag) {
			dnaflag1 = check_dnaflag(seq1,l1);
		        if(i == 1) dnaflag = dnaflag1;
		}
		else
			dnaflag1 = dnaflag;

		if( (!explicit_dnaflag) && (dnaflag1 != dnaflag) )
			warning(
	"Sequence %d [%s] appears to be of different type to sequence 1",
			i,sname1);

		if(dnaflag)
			n_encode(seq1,seq_array[i],l1);
		else
			p_encode(seq1,seq_array[i],l1);
	}

	fclose(fin);
	return no_seqs;
}
