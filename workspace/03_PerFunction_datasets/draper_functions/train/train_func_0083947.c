ast_jb_do_usecheck(struct ast_channel *c0, struct ast_channel *c1)
{
	struct ast_jb *jb0 = ast_channel_jb(c0);
	struct ast_jb *jb1 = ast_channel_jb(c1);
	struct ast_jb_conf *conf0 = &jb0->conf;
	struct ast_jb_conf *conf1 = &jb1->conf;
	int c0_wants_jitter = ast_channel_tech(c0)->properties & AST_CHAN_TP_WANTSJITTER;
	int c0_creates_jitter = ast_channel_tech(c0)->properties & AST_CHAN_TP_CREATESJITTER;
	int c0_jb_enabled = ast_test_flag(conf0, AST_JB_ENABLED);
	int c0_force_jb = ast_test_flag(conf0, AST_JB_FORCED);
	int c0_jb_timebase_initialized = ast_test_flag(jb0, JB_TIMEBASE_INITIALIZED);
	int c0_jb_created = ast_test_flag(jb0, JB_CREATED);
	int c1_wants_jitter = ast_channel_tech(c1)->properties & AST_CHAN_TP_WANTSJITTER;
	int c1_creates_jitter = ast_channel_tech(c1)->properties & AST_CHAN_TP_CREATESJITTER;
	int c1_jb_enabled = ast_test_flag(conf1, AST_JB_ENABLED);
	int c1_force_jb = ast_test_flag(conf1, AST_JB_FORCED);
	int c1_jb_timebase_initialized = ast_test_flag(jb1, JB_TIMEBASE_INITIALIZED);
	int c1_jb_created = ast_test_flag(jb1, JB_CREATED);
	int inuse = 0;


	if (((!c0_wants_jitter && c1_creates_jitter) || (c0_force_jb && c1_creates_jitter)) && c0_jb_enabled) {
		ast_set_flag(jb0, JB_USE);
		if (!c0_jb_timebase_initialized) {
			if (c1_jb_timebase_initialized) {
				memcpy(&jb0->timebase, &jb1->timebase, sizeof(struct timeval));
			} else {
				gettimeofday(&jb0->timebase, NULL);
			}
			ast_set_flag(jb0, JB_TIMEBASE_INITIALIZED);
		}

		if (!c0_jb_created) {
			jb_choose_impl(c0);
		}

		inuse = 1;
	}


	if (((!c1_wants_jitter && c0_creates_jitter) || (c1_force_jb && c0_creates_jitter)) && c1_jb_enabled) {
		ast_set_flag(jb1, JB_USE);
		if (!c1_jb_timebase_initialized) {
			if (c0_jb_timebase_initialized) {
				memcpy(&jb1->timebase, &jb0->timebase, sizeof(struct timeval));
			} else {
				gettimeofday(&jb1->timebase, NULL);
			}
			ast_set_flag(jb1, JB_TIMEBASE_INITIALIZED);
		}

		if (!c1_jb_created) {
			jb_choose_impl(c1);
		}

		inuse = 1;
	}

	return inuse;
}
