bam_aux_getCEi(bam1_t *b, int i)
{
	int cs_i;
	uint8_t *c = bam_aux_get(b, "CS");
	char *cs = NULL;
	char prev_b, cur_b;
	char cur_color, cor_color;


	if(0 == c) return 0;

	cs = bam_aux2Z(c);


	if(bam1_strand(b)) {
		cs_i = strlen(cs) - 1 - i;

		cur_color = cs[cs_i];

		prev_b = (cs_i == 1) ? "TGCAN"[(int)bam_aux_nt2int(cs[0])] : bam_nt16_rev_table[bam1_seqi(bam1_seq(b), i+1)];

		cur_b = bam_nt16_rev_table[bam1_seqi(bam1_seq(b), i)];
	}
	else {
		cs_i=i+1;

		cur_color = cs[cs_i];

		prev_b = (0 == i) ? cs[0] : bam_nt16_rev_table[bam1_seqi(bam1_seq(b), i-1)];

		cur_b = bam_nt16_rev_table[bam1_seqi(bam1_seq(b), i)];
	}


	cor_color = bam_aux_ntnt2cs(prev_b, cur_b);

	if(cur_color == cor_color) {
		return '-';
	}
	else {
		return cur_color;
	}
}
