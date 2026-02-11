got_PingAck(struct drbd_connection *connection, struct packet_info *pi)
{

	connection->meta.socket->sk->sk_rcvtimeo = connection->net_conf->ping_int*HZ;
	if (!test_and_set_bit(GOT_PING_ACK, &connection->flags))
		wake_up(&connection->ping_wait);

	return 0;
}
