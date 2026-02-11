listConvert(const siglist& a)
{
	int 	n = a.size();
	Tree 	t=nil;
	while (n--) t = cons(a[n],t);
	return t;
}
