gg_dcc7_session_remove(struct gg_session *sess, struct gg_dcc7 *dcc)
{
	struct gg_dcc7 *tmp;

	gg_debug_session(sess, GG_DEBUG_FUNCTION, "** gg_dcc7_session_remove(%p, %p)\n", sess, dcc);

	if (sess == NULL || dcc == NULL) {
		gg_debug_session(sess, GG_DEBUG_MISC, "// gg_dcc7_session_remove() invalid parameters\n");
		errno = EINVAL;
		return -1;
	}

	if (sess->dcc7_list == dcc) {
		sess->dcc7_list = dcc->next;
		dcc->next = NULL;
		return 0;
	}

	for (tmp = sess->dcc7_list; tmp != NULL; tmp = tmp->next) {
		if (tmp->next == dcc) {
			tmp->next = dcc->next;
			dcc->next = NULL;
			return 0;
		}
	}

	errno = ENOENT;
	return -1;
}
