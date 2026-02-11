bam_aux_getCSi(bam1_t *b, int i)
{
	uint8_t *c = bam_aux_get(b, "CS");
	char *cs = NULL;


	if(0 == c) return 0;

	cs = bam_aux2Z(c);

	if(bam1_strand(b)) {
	    i = strlen(cs) - 1 - i;

	    uint32_t cigar = bam1_cigar(b)[0];
	    if((cigar & BAM_CIGAR_MASK) == BAM_CHARD_CLIP) {
		i -= cigar >> BAM_CIGAR_SHIFT;
	    }
	} else { i++; }
	return cs[i];
}
