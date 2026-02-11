TRANS_case(void)
{
	int i;
	short pos;
	short local;

	control_check(RS_SELECT, "CASE without SELECT", "CASE");

	if (current_ctrl->state)
		THROW("Default case must be the last one");

	trans_select_break(FALSE);

	local = current_ctrl->local;

	control_enter(RS_CASE);

	for(i = 0; ; i++)
	{
		if (i > MAX_CASE_EXPR)
			THROW("Too many expressions in CASE");

		if (PATTERN_is_newline_end(*JOB->current))
			THROW("Unexpected end of line");


		if (TRANS_is(RS_TO))
		{
			CODE_push_local(local);
			TRANS_expression(FALSE);
			CODE_op(C_LE, 0, 2, TRUE);
		}
		else if (TRANS_is(RS_LIKE))
		{
			CODE_push_local(local);
			TRANS_expression(FALSE);
			CODE_op(C_LIKE, 0, 2, TRUE);
		}
		else
		{
			TRANS_expression(FALSE);

			if (TRANS_is(RS_TO))
			{
				CODE_push_local(local);
				CODE_op(C_LE, 0, 2, TRUE);
				CODE_push_local(local);
				TRANS_expression(FALSE);
				CODE_op(C_LE, 0, 2, TRUE);
				CODE_op(C_AND, 0, 2, TRUE);
			}
			else
			{
				CODE_push_local(local);
				CODE_op(C_EQ, 0, 2, TRUE);
			}
		}

		if (!PATTERN_is(*JOB->current, RS_COMMA))
		{
			pos = CODE_get_current_pos();
			CODE_jump_if_false();
			break;
		}

		control_add_current_pos();
		CODE_jump_if_true();

		JOB->current++;
	}

	control_jump_each_pos();
	control_leave();

	current_ctrl->value = pos;
}
