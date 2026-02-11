rfc2045_alloc_ac()
{
struct rfc2045 *p=rfc2045_alloc();

	if (p)	p->rfc2045acptr= &rfc2045acprep;
	currwp=0;
	return (p);
}
