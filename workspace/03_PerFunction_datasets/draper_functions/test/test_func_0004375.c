is_our_turn(struct queue_ent *qe)
{
	struct queue_ent *ch;
	int res;
	int avl;
	int idx = 0;

	ao2_lock(qe->parent);

	avl = num_available_members(qe->parent);

	ch = qe->parent->head;

	ast_debug(1, "There %s %d available %s.\n", avl != 1 ? "are" : "is", avl, avl != 1 ? "members" : "member");

	while ((idx < avl) && (ch) && (ch != qe)) {
		if (!ch->pending) {
			idx++;
		}
		ch = ch->next;
	}

	ao2_unlock(qe->parent);


	if (ch && idx < avl && (qe->parent->autofill || qe->pos == 1)) {
		ast_debug(1, "It's our turn (%s).\n", ast_channel_name(qe->chan));
		res = 1;
	} else {
		ast_debug(1, "It's not our turn (%s).\n", ast_channel_name(qe->chan));
		res = 0;
	}

	return res;
}
