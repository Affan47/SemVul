manager_queue_member_penalty(struct mansession *s, const struct message *m)
{
	const char *queuename, *interface, *penalty_s;
	int penalty;

	interface = astman_get_header(m, "Interface");
	penalty_s = astman_get_header(m, "Penalty");

	queuename = astman_get_header(m, "Queue");

	if (ast_strlen_zero(interface) || ast_strlen_zero(penalty_s)) {
		astman_send_error(s, m, "Need 'Interface' and 'Penalty' parameters.");
		return 0;
	}

	penalty = atoi(penalty_s);

	if (set_member_value((char *)queuename, (char *)interface, MEMBER_PENALTY, penalty)) {
		astman_send_error(s, m, "Invalid interface, queuename or penalty");
	} else {
		astman_send_ack(s, m, "Interface penalty set successfully");
	}

	return 0;
}
