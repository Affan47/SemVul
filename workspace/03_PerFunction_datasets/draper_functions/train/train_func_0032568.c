ast_dial_set_global_timeout(struct ast_dial *dial, int timeout)
{
	dial->timeout = timeout;

	if (dial->timeout > 0 && (dial->actual_timeout > dial->timeout || dial->actual_timeout == -1))
		dial->actual_timeout = dial->timeout;

	return;
}
