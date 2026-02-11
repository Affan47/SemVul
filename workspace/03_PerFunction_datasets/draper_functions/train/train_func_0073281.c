ooh323_answer(struct ast_channel *ast)
{
	struct ooh323_pvt *p = ast_channel_tech_pvt(ast);
	char *callToken = (char *)NULL;

	if (gH323Debug)
		ast_verb(0, "--- ooh323_answer\n");

	if (p) {

		ast_mutex_lock(&p->lock);
		callToken = (p->callToken ? strdup(p->callToken) : NULL);
		if (ast_channel_state(ast) != AST_STATE_UP) {
			ast_channel_lock(ast);
			if (!p->alertsent) {
	    			if (gH323Debug) {
					ast_debug(1, "Sending forced ringback for %s, res = %d\n",
						callToken, ooManualRingback(callToken));
				} else {
	    				ooManualRingback(callToken);
				}
				p->alertsent = 1;
			}
			ast_setstate(ast, AST_STATE_UP);
      			if (option_debug)
				ast_debug(1, "ooh323_answer(%s)\n", ast_channel_name(ast));
			ast_channel_unlock(ast);
			ooAnswerCall(p->callToken);
		}
		if (callToken) {
			free(callToken);
		}
		ast_mutex_unlock(&p->lock);
	}

	if (gH323Debug)
		ast_verb(0, "+++ ooh323_answer\n");

  return 0;
}
