ooh323_queryoption(struct ast_channel *ast, int option, void *data, int *datalen)
{

	struct ooh323_pvt *p = (struct ooh323_pvt *) ast_channel_tech_pvt(ast);
	int res = -1;
	enum ast_t38_state state = T38_STATE_UNAVAILABLE;
	char* cp;

	if (!p) return -1;

	ast_mutex_lock(&p->lock);

	if (gH323Debug)
		ast_verb(0, "----- ooh323_queryoption %d on channel %s\n", option, ast_channel_name(ast));

	switch (option) {

		case AST_OPTION_T38_STATE:

			if (*datalen != sizeof(enum ast_t38_state)) {
				ast_log(LOG_ERROR, "Invalid datalen for AST_OPTION_T38_STATE option."
				" Expected %d, got %d\n", (int)sizeof(enum ast_t38_state), *datalen);
				break;
			}

			if (p->t38support != T38_DISABLED) {
				if (p->faxmode) {
					state = (p->chmodepend) ? T38_STATE_NEGOTIATING : T38_STATE_NEGOTIATED;
				} else {
					state = T38_STATE_UNKNOWN;
				}
			}

			*((enum ast_t38_state *) data) = state;
			res = 0;
			break;


		case AST_OPTION_DIGIT_DETECT:

			cp = (char *) data;
			*cp = p->vad ? 1 : 0;
			ast_debug(1, "Reporting digit detection %sabled on %s\n",
							 *cp ? "en" : "dis", ast_channel_name(ast));

			res = 0;
			break;

		default:	;

	}

	if (gH323Debug)
		ast_verb(0, "+++++ ooh323_queryoption %d on channel %s\n", option, ast_channel_name(ast));

   	ast_mutex_unlock(&p->lock);

	return res;
}
