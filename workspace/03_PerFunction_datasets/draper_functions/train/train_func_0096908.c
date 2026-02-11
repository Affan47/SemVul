xdr_gf1_cli_get_volume (XDR *xdrs, gf1_cli_get_volume *objp)
{
	register int32_t *buf;
        buf = NULL;

	 if (!xdr_enum (xdrs, (enum_t *) objp))
		 return FALSE;
	return TRUE;
}
