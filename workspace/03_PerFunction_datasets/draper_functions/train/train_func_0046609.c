free_all_acl(struct target *target)
{
	struct isns_initiator *ini;

	while (!list_empty(&target->isns_head)) {
		ini = list_entry(target->isns_head.q_forw, typeof(*ini), ilist);
		remque(&ini->ilist);
		free(ini);
	}
}
