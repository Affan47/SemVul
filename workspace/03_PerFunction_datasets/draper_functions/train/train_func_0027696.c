scramble(void)
{

	do
	{
		int a_idx;


		for (a_idx = 1; a_idx < z_info->a_max; a_idx++)
		{
			scramble_artifact(a_idx);
		}
	} while (!artifacts_acceptable());


	return (0);
}
