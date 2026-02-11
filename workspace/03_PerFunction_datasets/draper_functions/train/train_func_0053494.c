read_sequences_stockholm(struct alignment* aln,char* string)
{
	int c = 0;
	int n = 0;
	int i = 0;
	int j = 0;
	char *p1 = 0;

	int aacode[26] = {0,1,2,3,4,5,6,7,8,-1,9,10,11,12,23,13,14,15,16,17,17,18,19,20,21,22};


	c = 0;
	while(aln->sl[c]){
		c++;
	}

	p1 = string;
	while((i = byg_end("\n",p1))!=-1){
		p1+=i;
		if (!(byg_start("//",p1))){
			break;
		}
		j = byg_end("#",p1);
		if(j != 1){
			j = byg_start(" ",p1);
			aln->lsn[c] = j;
			aln->sn[c] = malloc(sizeof(char)*(j+1));
			for (i = 0;i < j;i++){
				aln->sn[c][i] = p1[i];
			}
			aln->sn[c][j] = 0;


			p1+=j;
			j = byg_start("\n",p1);

			aln->s[c] = malloc(sizeof(int)*(j+1));
			aln->seq[c] = malloc(sizeof(char)*(j+1));
			n = 0;
			for (i = 0;i < j;i++){
				if(isalpha((int)p1[i])){
					aln->s[c][n] = aacode[toupper(p1[i])-65];
					aln->seq[c][n] = p1[i];
					n++;
				}
			}
			aln->s[c][n] = 0;
			aln->seq[c][n] = 0;
			aln->sl[c] = n;
			c++;
		}
	}

	free(string);
	return aln;
}
