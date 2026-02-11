keep_consistency_sub_script(Operand* dstop, Operand* srcop)
{
    int  i;

    if (dstop->sub != NULL) {
	free(dstop->sub);
    }
    dstop->nsub = srcop->nsub;
    if ((dstop->sub = calloc(dstop->nsub, sizeof(Sub_data*))) == NULL) {
	fatal("No room for Sub_data.\n");
    }
    for (i = 0; i < srcop->nsub; i++) {
	dstop->sub[i] = copy_all_sub_data(srcop->sub[i]);
    }
}
