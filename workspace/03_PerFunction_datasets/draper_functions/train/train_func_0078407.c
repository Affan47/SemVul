n_encode(char *seq,char *naseq,sint l)
{
	register sint i;


	for(i=1;i<=l;i++) {
    	if(seq[i] == '-')
			naseq[i] = gap_pos2;
		else {
			naseq[i]=res_index(amino_acid_codes,seq[i]);
		}
	}
	naseq[i] = -3;
}
