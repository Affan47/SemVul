rcuhead_fixup_activate(void *addr, enum debug_obj_state state)
{
	struct rcu_head *head = addr;

	switch (state) {

	case ODEBUG_STATE_NOTAVAILABLE:


		debug_object_init(head, &rcuhead_debug_descr);
		debug_object_activate(head, &rcuhead_debug_descr);
		return 0;
	default:
		return 1;
	}
}
