glpk_solver_factory_functional (GnmSolverFactory *factory,
				WBCGtk *wbcg)
{
	const char *full_path = gnm_conf_get_plugin_glpk_glpsol_path ();
	char *path;

	if (full_path && *full_path)
		return g_file_test (full_path, G_FILE_TEST_IS_EXECUTABLE);

	path = g_find_program_in_path (SOLVER_PROGRAM);
	if (path) {
		g_free (path);
		return TRUE;
	}

	if (!wbcg)
		return FALSE;

	path = gnm_sub_solver_locate_binary (SOLVER_PROGRAM,
					     "Gnu Linear Programming Kit",
					     SOLVER_URL,
					     wbcg);
	if (path) {
		gnm_conf_set_plugin_glpk_glpsol_path (path);
		g_free (path);
		return TRUE;
	}

	return FALSE;
}
