command_frame(const char *cmd)
{
	int i;
	int frame;
	STACK_CONTEXT *context = NULL;

	if (cmd)
	{
		frame = atoi(&cmd[1]);


		if (frame > 0)
		{
			for (i = 0;; i++)
			{
				context = GB_DEBUG.GetStack(i);
				if (!context)
					break;
				if (!context->pc && !context->cp)
					continue;

				frame--;
				if (!frame)
				{
					DEBUG_info.bp = context->bp;
					DEBUG_info.fp = context->fp;
					DEBUG_info.op = context->op;
					DEBUG_info.cp = context->cp;
					break;
				}
			}
		}
	}

	if (!context)
	{
		DEBUG_info.bp = BP;
		DEBUG_info.fp = FP;
		DEBUG_info.op = OP;
		DEBUG_info.cp = CP;
	}

	debug_info();
}
