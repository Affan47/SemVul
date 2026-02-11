buildin_hideoffnpc(struct script_state *st)
{
	struct npc_data *nd;

	if(st->end > st->start+2) {
		char *name = conv_str(st,& (st->stack->stack_data[st->start+2]));
		nd = npc_name2id(name);
		if(nd == NULL) {
			return 0;
		}
	} else {
		nd = map_id2nd(st->oid);
		if(nd == NULL) {
			printf("buildin_hideoffnpc: fatal error: npc not attached\n");
			return 0;
		}
	}
	npc_enable(nd->exname,2);
	return 0;
}
