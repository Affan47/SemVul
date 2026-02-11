wait_for_children(ulong waitflag)
{
        int status, pid;

	while (TRUE) {
        	switch (pid = waitpid(-1, &status, WNOHANG))
        	{
        	case  0:
			if (CRASHDEBUG(2))
			    console("wait_for_children: child running...\n");
			if (waitflag == ZOMBIES_ONLY)
				return;
			break;

        	case -1:
			if (CRASHDEBUG(2))
			    console("wait_for_children: no children alive\n");
                	return;

        	default:
			console("wait_for_children(%d): reaped %d\n",
				waitflag, pid);
			if (CRASHDEBUG(2))
			    fprintf(fp, "wait_for_children: reaped %d\n", pid);
                	break;
        	}
		stall(1000);
	}
}
