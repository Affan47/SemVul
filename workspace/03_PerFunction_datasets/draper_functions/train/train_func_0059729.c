wait_for_workers_to_finish (void)
{
	while (!sgen_workers_all_done ())
		g_usleep (200);
}
