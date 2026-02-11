gfire_filetransfer_chunk_done(gfire_filetransfer *p_transfer)
{

	const guint8 *chunk_data = gfire_file_chunk_get_data(p_transfer->chunk);

	lseek64(p_transfer->file, gfire_file_chunk_get_offset(p_transfer->chunk), SEEK_SET);
	if(write(p_transfer->file, chunk_data, gfire_file_chunk_get_size(p_transfer->chunk)) < 0)
	{
		purple_xfer_error(PURPLE_XFER_RECEIVE, purple_xfer_get_account(p_transfer->xfer),
						  purple_xfer_get_remote_user(p_transfer->xfer),
						  _("Writing a chunk failed! Make sure you have enough drive space "
							"and appropriate permissions!"));


		gfire_p2p_session_remove_file_transfer(p_transfer->session, p_transfer, TRUE);
		return;
	}


	if(++p_transfer->current_chunk == p_transfer->chunk_count)
	{
		gfire_p2p_dl_proto_send_file_complete(p_transfer->session, p_transfer->fileid);
		purple_xfer_set_completed(p_transfer->xfer, TRUE);
		gfire_p2p_session_remove_file_transfer(p_transfer->session, p_transfer, TRUE);
		return;
	}


	guint64 offset = p_transfer->current_chunk * XFIRE_P2P_FT_CHUNK_SIZE;
	guint32 size = (p_transfer->current_chunk == p_transfer->chunk_count - 1) ?
				p_transfer->size % XFIRE_P2P_FT_CHUNK_SIZE : XFIRE_P2P_FT_CHUNK_SIZE;

	gfire_file_chunk_init(p_transfer->chunk, offset, size);
	gfire_file_chunk_start_transfer(p_transfer->chunk);
}
