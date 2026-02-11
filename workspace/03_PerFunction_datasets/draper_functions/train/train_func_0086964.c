ast_autoservice_stop(struct ast_channel *chan)
{
	int res = -1;
	struct asent *as, *removed = NULL;
	struct ast_frame *f;
	int chan_list_state;

	AST_LIST_LOCK(&aslist);


	chan_list_state = as_chan_list_state;


	AST_LIST_TRAVERSE_SAFE_BEGIN(&aslist, as, list) {
		if (as->chan == chan) {
			as->use_count--;
			if (as->use_count < 1) {
				AST_LIST_REMOVE_CURRENT(list);
				removed = as;
			}
			break;
		}
	}
	AST_LIST_TRAVERSE_SAFE_END;

	if (removed && asthread != AST_PTHREADT_NULL) {
		pthread_kill(asthread, SIGURG);
	}

	AST_LIST_UNLOCK(&aslist);

	if (!removed) {
		return 0;
	}


	while (chan_list_state == as_chan_list_state) {
		usleep(1000);
	}


	if (!ast_channel_softhangup_internal_flag(chan)) {
		res = 0;
	}

	if (!as->orig_end_dtmf_flag) {
		ast_clear_flag(ast_channel_flags(chan), AST_FLAG_END_DTMF_ONLY);
	}

	ast_channel_lock(chan);
	while ((f = AST_LIST_REMOVE_HEAD(&as->deferred_frames, frame_list))) {
		if (!((1 << f->frametype) & as->ignore_frame_types)) {
			ast_queue_frame_head(chan, f);
		}
		ast_frfree(f);
	}
	ast_channel_unlock(chan);

	free(as);

	return res;
}
