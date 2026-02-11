display(void *index, uchar *pattern, ulong length, ulong numc, ulong *numocc, uchar **snippet_text, ulong **snippet_lengths) {
		int l,r;
		int pos;
		ulong *occ, i, j, from, to, len, x;
		uchar *text_aux;
		CSA *SA=(CSA *) index;
		csa_bsearch(pattern,length,SA,&l,&r);
		*numocc = r-l+1;
		occ = csa_batchlookup2(SA,l,r);
		*snippet_lengths = (ulong *) malloc((*numocc)*sizeof(ulong));
		if (!(*snippet_lengths)) return 1;
		*snippet_text = (uchar *) malloc((*numocc)*(length+2*numc)*sizeof(uchar));
		if (!(*snippet_text)) return 1;
		text_aux=*snippet_text;

		for (i=0;i<(*numocc);i++) {
			x=occ[i];
			if (x>numc) from = x-numc;
			else from=0;
			to= ((int)(x+length+numc-1)<(int)(SA->n-1)?(x+length+numc-1):(SA->n-1));
			len =to-from+1;
			pos = csa_inverse(SA,from+1);
			for (j=0; (int)j<(int)len;j++) {
				text_aux[j] = csa_T(SA,pos);
				pos= csa_psi(SA,pos);
			}
			text_aux+=length+2*numc;
			(*snippet_lengths)[i] = len;
		}
		free(occ);
		return 0;
	}
