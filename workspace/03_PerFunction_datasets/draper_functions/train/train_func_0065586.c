can_ring_entry(struct queue_ent *qe, struct callattempt *call)
{
	if (call->member->paused) {
		ast_debug(1, "%s paused, can't receive call\n", call->interface);
		return 0;
	}

	if (!call->member->ringinuse && !member_status_available(call->member->status)) {
		ast_debug(1, "%s not available, can't receive call\n", call->interface);
		return 0;
	}

	if ((call->lastqueue && call->lastqueue->wrapuptime && (time(NULL) - call->lastcall < call->lastqueue->wrapuptime))
		|| (!call->lastqueue && qe->parent->wrapuptime && (time(NULL) - call->lastcall < qe->parent->wrapuptime))) {
		ast_debug(1, "Wrapuptime not yet expired on queue %s for %s\n",
			(call->lastqueue ? call->lastqueue->name : qe->parent->name),
			call->interface);
		return 0;
	}

	if (use_weight && compare_weight(qe->parent, call->member)) {
		ast_debug(1, "Priority queue delaying call to %s:%s\n",
			qe->parent->name, call->interface);
		return 0;
	}

	if (!call->member->ringinuse) {
		if (member_call_pending_set(call->member)) {
			ast_debug(1, "%s has another call pending, can't receive call\n",
				call->interface);
			return 0;
		}


		if (!member_status_available(get_queue_member_status(call->member))) {
			ast_debug(1, "%s actually not available, can't receive call\n",
				call->interface);
			member_call_pending_clear(call->member);
			return 0;
		}
	}

	return 1;
}
