jndex_merge_environment (void)
{
	int		i;

	for (i = 0; i < n_ji_environment; i++) {
		E_environment[nn_E_environment++] = ji_environment[i];
	}

	return 0;
}
