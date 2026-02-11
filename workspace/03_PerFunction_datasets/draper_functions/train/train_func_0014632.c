CardBlockL(b_type B)
{
	register unsigned char *b=B->b, *card = CARDINALITY_BLOCKS;
	register unsigned short *list=B->list;
	register long	i,n=0;

	while((i= *list) != END_BLOCK_LIST) {
		n+=card[b[i]]; list++;
	}
	return n;
}
