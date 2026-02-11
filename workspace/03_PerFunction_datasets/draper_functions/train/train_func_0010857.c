ast_sched_del(struct ast_sched_context *con, int id)
#else
int _ast_sched_del(struct ast_sched_context *con, int id, const char *file, int line, const char *function)
#endif
{
	struct sched *s, tmp = {
		.id = id,
	};
	int *last_id = ast_threadstorage_get(&last_del_id, sizeof(int));

	DEBUG(ast_debug(1, "ast_sched_del(%d)\n", id));

	if (id < 0) {
		return 0;
	}

	ast_mutex_lock(&con->lock);
	s = ast_hashtab_lookup(con->schedq_ht, &tmp);
	if (s) {
		if (!ast_heap_remove(con->sched_heap, s)) {
			ast_log(LOG_WARNING,"sched entry %d not in the sched heap?\n", s->id);
		}

		if (!ast_hashtab_remove_this_object(con->schedq_ht, s)) {
			ast_log(LOG_WARNING,"Found sched entry %d, then couldn't remove it?\n", s->id);
		}

		con->schedcnt--;

		sched_release(con, s);
	}

#ifdef DUMP_SCHEDULER

	if (option_debug)
		ast_sched_dump(con);
#endif
	if (con->sched_thread) {
		ast_cond_signal(&con->sched_thread->cond);
	}
	ast_mutex_unlock(&con->lock);

	if (!s && *last_id != id) {
		ast_debug(1, "Attempted to delete nonexistent schedule entry %d!\n", id);
#ifndef AST_DEVMODE
		ast_assert(s != NULL);
#else
		{
		char buf[100];
		snprintf(buf, sizeof(buf), "s != NULL, id=%d", id);
		_ast_assert(0, buf, file, line, function);
		}
#endif
		*last_id = id;
		return -1;
	} else if (!s) {
		return -1;
	}

	return 0;
}
