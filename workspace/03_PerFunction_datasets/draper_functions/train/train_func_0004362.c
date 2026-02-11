xdr_guestfs_int_application (XDR *xdrs, guestfs_int_application *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->app_name, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->app_display_name, ~0))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->app_epoch))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->app_version, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->app_release, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->app_install_path, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->app_trans_path, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->app_publisher, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->app_url, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->app_source_package, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->app_summary, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->app_description, ~0))
		 return FALSE;
	return TRUE;
}
