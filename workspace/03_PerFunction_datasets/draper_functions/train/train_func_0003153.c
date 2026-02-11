xdr_symlinkargs(XDR *xdrs, symlinkargs *objp)
{

	 register int32_t *buf=buf;

	 if (!xdr_diropargs(xdrs, &objp->from)) {
		 return (FALSE);
	 }
	 if (!xdr_nfspath(xdrs, &objp->to)) {
		 return (FALSE);
	 }
	 if (!xdr_sattr(xdrs, &objp->attributes)) {
		 return (FALSE);
	 }
	return (TRUE);
}
