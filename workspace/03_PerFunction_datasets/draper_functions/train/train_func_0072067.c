ssl_process_accept(mod_ctl_t * ctl, mod_ctl_buf_t * ctlb)
{
	conn_t *conn;
	int32_t id;

	conn = make_conn(ctl, ctlb->F[0], ctlb->F[1]);

	id = buf_to_int32(&ctlb->buf[1]);

	if(id >= 0)
		conn_add_id_hash(conn, id);
	SetSSL(conn);

	if(rb_get_type(conn->mod_fd) & RB_FD_UNKNOWN)
	{

		rb_set_type(conn->mod_fd, RB_FD_SOCKET);
	}
	if(rb_get_type(conn->mod_fd) == RB_FD_UNKNOWN)
		rb_set_type(conn->plain_fd, RB_FD_SOCKET);

	rb_ssl_start_accepted(ctlb->F[0], ssl_process_accept_cb, conn, 10);
}
