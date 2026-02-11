quant_write(FILE * fd, const struct Quant *quant)
{
    DCELL dLow, dHigh;
    CELL cLow, cHigh;
    int i;

    if (quant->truncate_only) {
	fprintf(fd, "truncate");
	return;
    }
    if (quant->round_only) {
	fprintf(fd, "round");
	return;
    }
    if (G_quant_get_neg_infinite_rule(quant, &dLow, &cLow) > 0)
	fprintf(fd, "*:%.20g:%d\n", dLow, cLow);

    if (G_quant_get_pos_infinite_rule(quant, &dLow, &cLow) > 0)
	fprintf(fd, "%.20g:*:%d\n", dLow, cLow);

    for (i = G_quant_nof_rules(quant) - 1; i >= 0; i--) {
	G_quant_get_ith_rule(quant, i, &dLow, &dHigh, &cLow, &cHigh);
	fprintf(fd, "%.20g:%.20g:%d", dLow, dHigh, cLow);
	if (cLow != cHigh)
	    fprintf(fd, ":%d", cHigh);
	fprintf(fd, "\n");
    }
}
