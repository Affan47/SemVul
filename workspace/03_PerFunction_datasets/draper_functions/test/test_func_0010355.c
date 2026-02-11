stktable_trash_expired(struct stktable *t)
{
	struct stksess *ts;
	struct eb32_node *eb;

	eb = eb32_lookup_ge(&t->exps, now_ms - TIMER_LOOK_BACK);

	while (1) {
		if (unlikely(!eb)) {


			eb = eb32_first(&t->exps);
			if (likely(!eb))
				break;
		}

		if (likely(tick_is_lt(now_ms, eb->key))) {

			t->exp_next = eb->key;
			return t->exp_next;
		}


		ts = eb32_entry(eb, struct stksess, exps);
		eb = eb32_next(eb);

		eb32_delete(&ts->exps);

		if (!tick_is_expired(ts->expire, now_ms)) {
			if (!tick_isset(ts->expire))
				continue;

			ts->exps.key = ts->expire;
			eb32_insert(&t->exps, &ts->exps);

			if (!eb || eb->key > ts->exps.key)
				eb = &ts->exps;
			continue;
		}


		ebmb_delete(&ts->keys);
		stksess_free(t, ts);
	}


	t->exp_next = TICK_ETERNITY;
	return t->exp_next;
}
