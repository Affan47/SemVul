prconr(FILEP fp, Constp x, int k)
#endif
{
	char *x0, *x1;
	char cdsbuf0[64], cdsbuf1[64];

	if (k > 1) {
		if (x->vstg) {
			x0 = x->Const.cds[0];
			x1 = x->Const.cds[1];
			}
		else {
			x0 = cds(dtos(x->Const.cd[0]), cdsbuf0);
			x1 = cds(dtos(x->Const.cd[1]), cdsbuf1);
			}
		fprintf(fp, "\t%s %s\n", x0, x1);
		}
	else
		fprintf(fp, "\t%s\n", x->vstg ? x->Const.cds[0]
				: cds(dtos(x->Const.cd[0]), cdsbuf0));
}
