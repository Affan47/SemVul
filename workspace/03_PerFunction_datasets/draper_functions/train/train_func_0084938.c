audit_print_reply(struct audit_reply *rep, int fd)
{
	_audit_elf = 0;

	switch (rep->type) {
		case NLMSG_NOOP:
			return 1;
		case NLMSG_DONE:

			audit_close(fd);
			if (printed == 0)
				printf("No rules\n");
			else {
				lnode *n;
				list_first(&l);
				n = l.cur;
				while (n) {
					print_rule(n->r);
					n = list_next(&l);
				}
				list_clear(&l);
			}
			break;
		case NLMSG_ERROR:
		        printf("NLMSG_ERROR %d (%s)\n",
				-rep->error->error,
				strerror(-rep->error->error));
			printed = 1;
			break;
		case AUDIT_GET:
			printf("AUDIT_STATUS: enabled=%d flag=%d pid=%d"
			" rate_limit=%d backlog_limit=%d lost=%d backlog=%u\n",
			rep->status->enabled, rep->status->failure,
			rep->status->pid, rep->status->rate_limit,
			rep->status->backlog_limit, rep->status->lost,
			rep->status->backlog);
			printed = 1;
			break;
		case AUDIT_LIST_RULES:
			list_requested = 0;
			if (key_match(rep->ruledata))
				 list_append(&l, rep->ruledata,
					sizeof(struct audit_rule_data) +
					rep->ruledata->buflen);
			printed = 1;
			return 1;
		default:
			printf("Unknown: type=%d, len=%d\n", rep->type,
				rep->nlh->nlmsg_len);
			printed = 1;
			break;
	}
	return 0;
}
