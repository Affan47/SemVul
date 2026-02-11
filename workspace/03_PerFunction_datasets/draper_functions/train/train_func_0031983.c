page_state_callback(struct ast_dial *dial)
{
	struct ast_channel *chan;
	struct page_options *options;

	if (ast_dial_state(dial) != AST_DIAL_RESULT_ANSWERED ||
	    !(chan = ast_dial_answered(dial)) ||
	    !(options = ast_dial_get_user_data(dial))) {
		return;
	}

	setup_profile_bridge(chan, options);
	setup_profile_paged(chan, options);
}
