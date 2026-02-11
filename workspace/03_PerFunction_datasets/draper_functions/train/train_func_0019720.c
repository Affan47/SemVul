realpart(register Addrp p)
#endif
{
	register Addrp q;

	if (p->tag == TADDR
	 && p->uname_tag == UNAM_CONST
	 && ISCOMPLEX (p->vtype))
		return (Addrp)mkrealcon (p -> vtype + TYREAL - TYCOMPLEX,
			p->user.kludge.vstg1 ? p->user.Const.cds[0]
				: cds(dtos(p->user.Const.cd[0]),CNULL));

	q = (Addrp) cpexpr((expptr) p);
	if( ISCOMPLEX(p->vtype) )
		q = mkfield (q, "r", p -> vtype + TYREAL - TYCOMPLEX);

	return(q);
}
