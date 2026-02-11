ndmis_tcp_close (struct ndm_session *sess)
{
	struct ndm_image_stream *is = &sess->plumb.image_stream;

	switch (is->remote.connect_status) {
	case NDMIS_CONN_LISTEN:
		ndmchan_cleanup (&is->remote.listen_chan);
		break;

	case NDMIS_CONN_CONNECTED:
	case NDMIS_CONN_ACCEPTED:
		ndmchan_cleanup (&is->chan);
		break;

	default:
		break;
	}

	ndmis_reinit_remote (sess);

	return 0;
}
