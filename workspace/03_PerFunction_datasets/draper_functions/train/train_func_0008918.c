vrrp_sync_fault(vrrp_t * vrrp)
{
	vrrp_t *isync;
	vrrp_sgroup_t *vgroup = vrrp->sync;
	list l = vgroup->index_list;
	element e;

	if (GROUP_STATE(vgroup) == VRRP_STATE_FAULT)
		return;

	log_message(LOG_INFO, "VRRP_Group(%s) Syncing instances to FAULT state",
	       GROUP_NAME(vgroup));


	for (e = LIST_HEAD(l); e; ELEMENT_NEXT(e)) {
		isync = ELEMENT_DATA(e);


		if (isync != vrrp && isync->state != VRRP_STATE_FAULT) {
			if (isync->state == VRRP_STATE_MAST)
				isync->wantstate = VRRP_STATE_GOTO_FAULT;
			if (isync->state == VRRP_STATE_BACK)
				isync->state = VRRP_STATE_FAULT;
		}
	}
	vgroup->state = VRRP_STATE_FAULT;
	notify_group_exec(vgroup, VRRP_STATE_FAULT);
#ifdef _WITH_SNMP_
	vrrp_snmp_group_trap(vgroup);
#endif
}
