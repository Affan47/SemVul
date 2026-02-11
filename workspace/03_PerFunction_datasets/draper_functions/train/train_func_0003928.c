IntersectBlockCF(b_type B1, b_type B2,b_type IB)

{
	register unsigned char *b1=B1->b,*b2=B2->b,*ib=IB->b;
	register unsigned short *list=B2->list;
	register unsigned short *newlist=IB->list;
	register unsigned char *card = CARDINALITY_BLOCKS;
	register long i,k,a,n=0;


	for(n=a=k=0; (i=list[a]) != END_BLOCK_LIST; a++){
	   if((ib[i]=b1[i]) & b2[i]) {
		newlist[k++]=i; n+=card[(ib[i])];
	   }
	}
	newlist[k]= END_BLOCK_LIST;
	return n;
}
