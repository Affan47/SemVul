skinny_answer(struct ast_channel *ast)
{
	int res = 0;
	struct skinny_subchannel *sub = ast_channel_tech_pvt(ast);

	if (sub->blindxfer) {
		SKINNY_DEBUG(DEBUG_SUB, 3, "skinny_answer(%s) on %s@%s-%d with BlindXFER, transferring\n",
			ast_channel_name(ast), sub->line->name, sub->line->device->name, sub->callid);
		ast_setstate(ast, AST_STATE_UP);
		skinny_transfer(sub);
		return 0;
	}

	sub->cxmode = SKINNY_CX_SENDRECV;

	SKINNY_DEBUG(DEBUG_SUB, 3, "skinny_answer(%s) on %s@%s-%d\n",
		ast_channel_name(ast), sub->line->name, sub->line->device->name, sub->callid);

	setsubstate(sub, SUBSTATE_CONNECTED);

	return res;
}
