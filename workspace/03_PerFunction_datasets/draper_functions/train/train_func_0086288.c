close_conn(conn_t * conn, int wait_plain, const char *fmt, ...)
{
	va_list ap;
	char reason[128];
	char buf[256];
	int len;
	if(IsDead(conn))
		return;

	rb_rawbuf_flush(conn->modbuf_out, conn->mod_fd);
	rb_rawbuf_flush(conn->plainbuf_out, conn->plain_fd);
	rb_close(conn->mod_fd);
	SetDead(conn);

	if(conn->id >= 0 && !IsZipSSL(conn))
		rb_dlinkDelete(&conn->node, connid_hash(conn->id));

	if(!wait_plain || fmt == NULL)
	{
		rb_close(conn->plain_fd);
		rb_dlinkAdd(conn, &conn->node, &dead_list);
		return;
	}
	rb_setselect(conn->plain_fd, RB_SELECT_READ, conn_plain_read_shutdown_cb, conn);
	rb_setselect(conn->plain_fd, RB_SELECT_WRITE, NULL, NULL);
	va_start(ap, fmt);
	rb_vsnprintf(reason, sizeof(reason), fmt, ap);
	va_end(ap);

	buf[0] = 'D';
	int32_to_buf(&buf[1], conn->id);
	strcpy(&buf[5], reason);
	len = (strlen(reason) + 1) + 5;
	mod_cmd_write_queue(conn->ctl, buf, len);
}
