do_jmp(int off)
{
	int i;
	ConsoleDebug(FUNCTIONS, "jmp: %d\n", off);

	if (off < 0)
	{
		ConsoleMessage("Can't have a negative relative jump offset\n");
		return;
	}
	for (i = 0; i < off; i++)
	{
		if (function_context.fp)
		{
			function_context.fp = function_context.fp->next;
		}
	}
}
