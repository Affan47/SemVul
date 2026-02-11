send_nossl_support(mod_ctl_t * ctl, mod_ctl_buf_t * ctlb)
{
	static const char *nossl_cmd = "N";
	conn_t *conn;
	int32_t id;

	if(ctlb != NULL)
	{
		conn = make_conn(ctl, ctlb->F[0], ctlb->F[1]);
		id = buf_to_int32(&ctlb->buf[1]);

		if(id >= 0)
			conn_add_id_hash(conn, id);
		close_conn(conn, WAIT_PLAIN, "libratbox reports no SSL/TLS support");
	}
	mod_cmd_write_queue(ctl, nossl_cmd, strlen(nossl_cmd));
}
