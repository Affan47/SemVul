UDBIndex_show(UDBIndex *self)
{
	PID_TYPE pid, maxPid = UDBIndex_pidCount(self);

	printf("UDBIndex: (pid/pos)\n\n");

	for (pid = 0; pid < maxPid; pid ++)
	{
		PID_TYPE pos = UDBIndex_posForPid_(self, pid);
		printf("  %i -> %i\n", (int)pid, (int)pos);
	}

	printf("\n");
}
