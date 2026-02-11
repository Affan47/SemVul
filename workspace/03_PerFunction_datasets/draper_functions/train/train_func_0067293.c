pprint_minmax_f(struct cloogoptions *info, FILE *dst, struct clast_reduction *r)
{
    int i;
    if (r->n == 0)
	return;
    fprintf(dst, r->type == clast_red_max ? "MAX(" : "MIN(");
    pprint_expr(info, dst, r->elts[0]);
    for (i = 1; i < r->n; ++i) {
	fprintf(dst, ",");
	pprint_expr(info, dst, r->elts[i]);
    }
    fprintf(dst, ")");
}
