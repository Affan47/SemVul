freeerr(ERROR *n)
{
	vsrm(n->file);
	vsrm(n->msg);
	enquef(ERROR, link, &errnodes, n);
}
