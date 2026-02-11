dump_entry(STRUCT_ENTRY *e, const TC_HANDLE_T handle)
{
	size_t i;
	STRUCT_ENTRY_TARGET *t;

	printf("Entry %u (%lu):\n", entry2index(handle, e),
	       entry2offset(handle, e));
	printf("SRC IP: %u.%u.%u.%u/%u.%u.%u.%u\n",
	       IP_PARTS(e->arp.src.s_addr),IP_PARTS(e->arp.smsk.s_addr));
	printf("DST IP: %u.%u.%u.%u/%u.%u.%u.%u\n",
	       IP_PARTS(e->arp.tgt.s_addr),IP_PARTS(e->arp.tmsk.s_addr));
	printf("Interface: `%s'/", e->arp.iniface);
	for (i = 0; i < IFNAMSIZ; i++)
		printf("%c", e->arp.iniface_mask[i] ? 'X' : '.');
	printf("to `%s'/", e->arp.outiface);
	for (i = 0; i < IFNAMSIZ; i++)
		printf("%c", e->arp.outiface_mask[i] ? 'X' : '.');
	printf("Flags: %02X\n", e->arp.flags);
	printf("Invflags: %02X\n", e->arp.invflags);
	printf("Counters: %llu packets, %llu bytes\n",
	       e->counters.pcnt, e->counters.bcnt);


	printf("\n");


	t = GET_TARGET(e);
	printf("Target name: `%s' [%u]\n", t->u.user.name, t->u.target_size);
	if (strcmp(t->u.user.name, STANDARD_TARGET) == 0) {
		int pos = *(int *)t->data;
		if (pos < 0)
			printf("verdict=%s\n",
			       pos == -NF_ACCEPT-1 ? "NF_ACCEPT"
			       : pos == -NF_DROP-1 ? "NF_DROP"
			       : pos == -NF_QUEUE-1 ? "NF_QUEUE"
			       : pos == RETURN ? "RETURN"
			       : "UNKNOWN");
		else
			printf("verdict=%u\n", pos);
	} else if (strcmp(t->u.user.name, ARPT_ERROR_TARGET) == 0)
		printf("error=`%s'\n", t->data);

	printf("\n");
	return 0;
}
