gfire_filetransfer_complete(gfire_filetransfer *p_transfer)
{
	if(!p_transfer || purple_xfer_get_type(p_transfer->xfer) != PURPLE_XFER_SEND)
		return;

	purple_xfer_set_completed(p_transfer->xfer, TRUE);
	gfire_p2p_session_remove_file_transfer(p_transfer->session, p_transfer, TRUE);
}
