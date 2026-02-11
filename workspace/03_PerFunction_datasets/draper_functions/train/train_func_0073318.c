reset()
{
	for (int i = 0; i < PATHMEM; i++) {
		memset(metrics[i], 0, nstates * sizeof(int));
		memset(history[i], 0, nstates * sizeof(int));
	}
	ptr = 0;
}
