gm_mcp_vmoo_userlist_handle_state(GmMcpVmooUserlist *package, MOOVar *v,
		UserState state, gboolean onOff) {
	MOOVar *nr;
	UserInfo *u;
	GmTriggerConditionType condition = 0;

	if (v->type != LIST) {
		return;
	}

	for (nr = v->list; nr; nr = nr->next) {
		if (nr->type == OBJECT) {
			if ((u = gm_mcp_vmoo_userlist_find_user(package, nr->i))) {
				switch (state) {
					case U_IDLE:
						if (u->state == U_IDLEAWAY && !onOff) {
							u->state = U_AWAY;
						} else if (u->state == U_AWAY && onOff) {
							u->state = U_IDLEAWAY;
						} else if (onOff) {
							u->state = U_IDLE;
						} else if (u->state == U_IDLE) {
							u->state = U_NORMAL;
						}

						if (onOff) {
							condition = TCT_USER_IDLE;
						} else {
							condition = TCT_USER_IDLE_OFF;
						}
					break;
					case U_AWAY:
						if (u->state == U_IDLEAWAY && !onOff) {
							u->state = U_IDLE;
						} else if (u->state == U_IDLE && onOff) {
							u->state = U_IDLEAWAY;
						} else if (onOff) {
							u->state = U_AWAY;
						} else if (u->state == U_AWAY) {
							u->state = U_NORMAL;
						}

						if (onOff) {
							condition = TCT_USER_AWAY;
						} else {
							condition = TCT_USER_AWAY_OFF;
						}
					break;
					default:
					break;
				}

				g_signal_emit_by_name(package, "state-changed", u->nr);

				if (condition != 0) {
					gm_mcp_vmoo_userlist_process_triggers(package, u->name,
							condition);
				}
			} else {
				gm_debug_msg(DEBUG_MCP, "User %d does not exist!", nr->i);
			}
		} else {
			gm_debug_msg(DEBUG_MCP, "Nr is not an object: %d", nr->type);
		}
	}
}
