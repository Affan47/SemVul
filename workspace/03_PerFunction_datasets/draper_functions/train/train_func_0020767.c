reload_single_member(const char *memberdata, struct call_queue *q)
{
	char *membername, *interface, *state_interface, *tmp;
	char *parse;
	struct member *cur, *newm;
	struct member tmpmem;
	int penalty;
	int ringinuse;
	AST_DECLARE_APP_ARGS(args,
		AST_APP_ARG(interface);
		AST_APP_ARG(penalty);
		AST_APP_ARG(membername);
		AST_APP_ARG(state_interface);
		AST_APP_ARG(ringinuse);
	);

	if (ast_strlen_zero(memberdata)) {
		ast_log(LOG_WARNING, "Empty queue member definition. Moving on!\n");
		return;
	}


	parse = ast_strdupa(memberdata);

	AST_STANDARD_APP_ARGS(args, parse);

	interface = args.interface;
	if (!ast_strlen_zero(args.penalty)) {
		tmp = args.penalty;
		ast_strip(tmp);
		penalty = atoi(tmp);
		if (penalty < 0) {
			penalty = 0;
		}
	} else {
		penalty = 0;
	}

	if (!ast_strlen_zero(args.membername)) {
		membername = args.membername;
		ast_strip(membername);
	} else {
		membername = interface;
	}

	if (!ast_strlen_zero(args.state_interface)) {
		state_interface = args.state_interface;
		ast_strip(state_interface);
	} else {
		state_interface = interface;
	}

	if (!ast_strlen_zero(args.ringinuse)) {
		tmp = args.ringinuse;
		ast_strip(tmp);
		if (ast_true(tmp)) {
			ringinuse = 1;
		} else if (ast_false(tmp)) {
			ringinuse = 0;
		} else {
			ast_log(LOG_ERROR, "Member %s has an invalid ringinuse value. Using %s ringinuse value.\n",
				membername, q->name);
			ringinuse = q->ringinuse;
		}
	} else {
		ringinuse = q->ringinuse;
	}


	ast_copy_string(tmpmem.interface, interface, sizeof(tmpmem.interface));
	cur = ao2_find(q->members, &tmpmem, OBJ_POINTER);

	if ((newm = create_queue_member(interface, membername, penalty, cur ? cur->paused : 0, state_interface, ringinuse))) {
		if (cur) {

			ao2_lock(q->members);
			newm->queuepos = cur->queuepos;
			ao2_link(q->members, newm);
			ao2_unlink(q->members, cur);
			ao2_unlock(q->members);
		} else {

			member_add_to_queue(q, newm);
		}
		ao2_ref(newm, -1);
	}
	newm = NULL;

	if (cur) {
		ao2_ref(cur, -1);
	}
}
