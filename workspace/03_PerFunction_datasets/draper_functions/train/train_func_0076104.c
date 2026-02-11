trans_if(void)
{
	int mode = RS_NONE;
	char *msg;

	TRANS_expression(FALSE);

	if (PATTERN_is(*JOB->current, RS_AND))
	{
		mode = RS_AND;
		msg = "AND IF";
	}
	else if (PATTERN_is(*JOB->current, RS_OR))
	{
		mode = RS_OR;
		msg = "OR IF";
	}

	if (mode != RS_NONE)
	{
		control_enter(RS_IF);


		control_set_value(trans_jump_if(mode == RS_AND));


		CODE_ignore_next_stack_usage();
		CODE_push_boolean(mode != RS_AND);

		for(;;)
		{
			if (!PATTERN_is(*JOB->current, mode))
				break;
			JOB->current++;

			TRANS_want(RS_IF, msg);


			trans_else();

			TRANS_expression(FALSE);


			control_set_value(trans_jump_if(mode == RS_AND));


			CODE_ignore_next_stack_usage();
			CODE_push_boolean(mode != RS_AND);

			if (PATTERN_is(*JOB->current, RS_THEN) || PATTERN_is_newline(*JOB->current))
				break;
		}


		trans_else();


		CODE_push_boolean(mode == RS_AND);
		trans_endif();

		control_leave();
	}

	if (PATTERN_is(*JOB->current, RS_THEN))
		JOB->current++;
	else if (!PATTERN_is_newline(*JOB->current))
		THROW(E_EXPECTED, "THEN");


	control_set_value(trans_jump_if(FALSE));
}
