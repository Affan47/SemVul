brasero_cdrdao_set_argv_blank (BraseroCdrdao *cdrdao,
			       GPtrArray *argv)
{
	BraseroBurnFlag flags;

	g_ptr_array_add (argv, g_strdup ("cdrdao"));
	g_ptr_array_add (argv, g_strdup ("blank"));

	brasero_cdrdao_set_argv_device (cdrdao, argv);
	brasero_cdrdao_set_argv_common (cdrdao, argv);

	g_ptr_array_add (argv, g_strdup ("--blank-mode"));
	brasero_job_get_flags (BRASERO_JOB (cdrdao), &flags);
	if (!(flags & BRASERO_BURN_FLAG_FAST_BLANK))
		g_ptr_array_add (argv, g_strdup ("full"));
	else
		g_ptr_array_add (argv, g_strdup ("minimal"));

	brasero_job_set_current_action (BRASERO_JOB (cdrdao),
					BRASERO_BURN_ACTION_BLANKING,
					NULL,
					FALSE);

	return BRASERO_BURN_OK;
}
