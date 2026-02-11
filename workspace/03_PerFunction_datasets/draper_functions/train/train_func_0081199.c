gfire_filetransfer_request_denied(PurpleXfer *p_xfer)
{
	if(!p_xfer)
		return;

	purple_debug_info("gfire", "P2P: file transfer request denied\n");

	gfire_filetransfer *ft = p_xfer->data;

	gfire_p2p_dl_proto_send_file_request_reply(ft->session, ft->fileid, FALSE);

	gfire_p2p_session_remove_file_transfer(ft->session, ft, TRUE);
}
