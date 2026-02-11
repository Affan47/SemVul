ERR_set_mark(void)
	{
	ERR_STATE *es;

	es=ERR_get_state();

	if (es->bottom == es->top) return 0;
	es->err_flags[es->top]|=ERR_FLAG_MARK;
	return 1;
	}
