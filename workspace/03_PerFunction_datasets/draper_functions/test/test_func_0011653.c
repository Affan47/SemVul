CatchupInterruptHandler(SIGNAL_ARGS)
{
	int			save_errno = errno;


	if (proc_exit_inprogress)
		return;

	if (catchupInterruptEnabled)
	{
		bool		save_ImmediateInterruptOK = ImmediateInterruptOK;


		ImmediateInterruptOK = false;


		catchupInterruptEnabled = 0;
		catchupInterruptOccurred = 1;
		for (;;)
		{
			catchupInterruptEnabled = 1;
			if (!catchupInterruptOccurred)
				break;
			catchupInterruptEnabled = 0;
			if (catchupInterruptOccurred)
			{

				ProcessCatchupEvent();
			}
		}


		ImmediateInterruptOK = save_ImmediateInterruptOK;
		if (save_ImmediateInterruptOK)
			CHECK_FOR_INTERRUPTS();
	}
	else
	{


		catchupInterruptOccurred = 1;
	}

	errno = save_errno;
}
