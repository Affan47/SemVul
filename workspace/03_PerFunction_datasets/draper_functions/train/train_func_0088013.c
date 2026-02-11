DefAutoExec(proc)
const data_obj	*(*proc) ptrproto((const char *));
{
	const data_obj	*d = (*proc)(ProcFmt);
	const char	*pattern;
	register struct AutoExec	*p;

	pattern = do_ask("\r\n", NULL_ASK_EXT, (char *) NULL, ": %f %s ", d->Name);
	for (p = AutoExecs; p != &AutoExecs[ExecIndex]; p++)
		if (p->a_cmd == d
		&& ((pattern == NULL || p->a_pattern == NULL)?
			(pattern == p->a_pattern) : (strcmp(pattern, p->a_pattern) == 0))
		&& p->a_arg_state == arg_state
		&& p->a_arg_count == arg_count)
			return;

	if (ExecIndex >= NEXECS)
		complain("Too many auto-executes, max %d.", NEXECS);
	p->a_pattern = copystr(pattern);
	p->a_cmd = d;
	p->a_arg_state = arg_state;
	p->a_arg_count = arg_count;
	ExecIndex += 1;
}
