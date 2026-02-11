ndmconn_unexpected_impl (struct ndmconn *conn, struct ndmp_msg_buf *nmb)
{
    NDMPConnection *self = NDMP_CONNECTION(conn->context);

    if (!ndmconn_handle_notify(self, nmb)) {
	g_warning("ignoring unrecognized, unexpected packet");
    }

    ndmconn_free_nmb(NULL, nmb);
}
