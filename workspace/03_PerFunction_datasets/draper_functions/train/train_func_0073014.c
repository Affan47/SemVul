share_check (struct stat *statbuf, guint32 sharemode,
			     guint32 fileaccess,
			     struct _WapiFileShare **share_info, int fd)
{
	if (share_allows_open (statbuf, sharemode, fileaccess,
			       share_info) == TRUE) {
		return (TRUE);
	}


	_wapi_handle_check_share (*share_info, fd);
	if (share_allows_open (statbuf, sharemode, fileaccess,
			       share_info) == TRUE) {
		return (TRUE);
	}


	_wapi_handle_collect ();

	return(share_allows_open (statbuf, sharemode, fileaccess, share_info));
}
