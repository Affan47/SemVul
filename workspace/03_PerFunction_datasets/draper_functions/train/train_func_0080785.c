xdr_mountlist (XDR *xdrs, mountlist *objp)
{
	register int32_t *buf;

	 if (!xdr_pointer (xdrs, (char **)objp, sizeof (struct mountbody), (xdrproc_t) xdr_mountbody))
		 return FALSE;
	return TRUE;
}
