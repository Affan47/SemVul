dump_rev(char *p, rev_t *r)
{
	printf("%s", p);
	if(r)
		printf("'%s', '%s', %d\n", r->rev, r->branch, r->isbranch);
	else
		printf("<null>\n");
}
