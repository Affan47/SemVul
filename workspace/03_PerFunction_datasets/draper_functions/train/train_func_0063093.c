pileup_seq(const bam_pileup1_t *p, int pos, int ref_len, const char *ref)
{
	if (p->is_head) printf("^%c", p->b->core.qual > 93? 126 : p->b->core.qual + 33);
	if (!p->is_del) {
		int j, rb, c = bam_nt16_rev_table[bam1_seqi(bam1_seq(p->b), p->qpos)];
		rb = (ref && pos < ref_len)? ref[pos] : 'N';
		if (c == '=' || toupper(c) == toupper(rb)) c = bam1_strand(p->b)? ',' : '.';
		else c = bam1_strand(p->b)? tolower(c) : toupper(c);
		putchar(c);
		if (p->indel > 0) {
			printf("+%d", p->indel);
			for (j = 1; j <= p->indel; ++j) {
				c = bam_nt16_rev_table[bam1_seqi(bam1_seq(p->b), p->qpos + j)];
				putchar(bam1_strand(p->b)? tolower(c) : toupper(c));
			}
		} else if (p->indel < 0) {
			printf("%d", p->indel);
			for (j = 1; j <= -p->indel; ++j) {
				c = (ref && (int)pos+j < ref_len)? ref[pos+j] : 'N';
				putchar(bam1_strand(p->b)? tolower(c) : toupper(c));
			}
		}
	} else putchar('*');
	if (p->is_tail) putchar('$');
}
