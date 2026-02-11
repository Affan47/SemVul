cmpnodes(GelETree *l, GelETree *r)
{
	int n=0;

	n=mpw_cmp(l->val.value,r->val.value);

	if G_UNLIKELY (gel_error_num) return 0;

	if(n>0) n=1;
	else if(n<0) n=-1;
	return n;
}
