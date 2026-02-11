upper(p)
register char	*p;
{
	if (jislower(*p)) {
		*p = CharUpcase(*p);
		return YES;
	}
	return NO;
}
