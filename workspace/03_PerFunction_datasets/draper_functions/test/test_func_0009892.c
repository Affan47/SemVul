print_ncbuf_region(Operand ***region, Quadruple ***region_qr, const int vpe_cnt)
{
    int i;

    for (i = 1; i < vpe_cnt; i++) {
	fprintf(stderr, "region[%d][0] : ", i);
	print_ncbuf_region_operand(region[i][0], region_qr[i][0]);

	fprintf(stderr, "region[%d][1] : ", i);
	print_ncbuf_region_operand(region[i][2], region_qr[i][1]);

	fprintf(stderr, "region[%d][2] : ", i);
	print_ncbuf_region_operand(region[i][2], region_qr[i][2]);
    }
}
