manager_iax2_show_peers(struct mansession *s, const struct message *m)
{
	static const char * const a[] = { "iax2", "show", "peers" };
	const char *id = astman_get_header(m,"ActionID");
	char idtext[256] = "";
	int total = 0;

	if (!ast_strlen_zero(id))
		snprintf(idtext, sizeof(idtext), "ActionID: %s\r\n", id);

	astman_send_listack(s, m, "Peer status list will follow", "start");

	__iax2_show_peers(-1, &total, s, 3, a);

        astman_append(s,
        "Event: PeerlistComplete\r\n"
        "EventList: Complete\r\n"
        "ListItems: %d\r\n"
        "%s"
        "\r\n", total, idtext);
        return 0;
}
