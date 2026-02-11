iosetip(int i, int offset)
#endif
{
	register expptr p;

	if(p = V(i))
		if(p->tag==TADDR &&
		    ONEOF(p->addrblock.vtype, inqmask) ) {
			ioset_assign = OPASSIGNI;
			ioset(TYADDR, offset, addrof(cpexpr(p)) );
			ioset_assign = OPASSIGN;
			}
		else
			errstr("impossible inquire parameter %s", ioc[i].iocname);
	else
		ioset(TYADDR, offset, ICON(0) );
}
