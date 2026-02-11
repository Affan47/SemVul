process_send_sockets(struct work_struct *work)
{
	struct connection *con = container_of(work, struct connection, swork);

	if (test_and_clear_bit(CF_CONNECT_PENDING, &con->flags))
		con->connect_action(con);
	if (test_and_clear_bit(CF_WRITE_PENDING, &con->flags))
		send_to_sock(con);
}
