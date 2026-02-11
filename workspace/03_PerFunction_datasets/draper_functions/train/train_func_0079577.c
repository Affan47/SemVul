MatcherGBlastOffset(e_type E, gb_typ B, long *os)
{
	long	num,n,q,score,s,c,d,e,i,j,hits=0,max,*tmp=B->tmp,maxoff=0;
	a_type	A=B->A;

	long	flank = *os;


	n = LenSeq(E) - 1; c = XnuSeq(1,E);
	q = B->d[c][0];
	for(max=0, i=2; i <= n; c=d, i++){
	   d = XnuSeq(i,E);
	   q = B->d[d][q];
	   e = XnuSeq(i+1,E);
	   if(!EmptyMList(q,B->pos[e])){
		num=GetListMList(tmp, q, B->pos[e]);
		for(j=0;  j < num; j++){
			s = tmp[j];

			score=WinExtendGBlast(B->E, s, E, i-1, A, flank);
			if(score > max){ max = score; maxoff = s+1; }


		} hits+=j;
	   }
	}
	*os = maxoff;
	return max;
}
