ExportToGhemical (Molecule *mol)
{
	char *cml = Build3D (mol);
	if (!cml)
		return;
	char *tmpname = g_strdup ("/tmp/gprXXXXXX.gpr");
	int f = g_mkstemp (tmpname);
	close (f);
	std::string uri = "file://";
	uri += tmpname;
	mol->GetDocument ()->GetApp ()->ConvertFromCML (cml, uri, "gpr");
	g_free (cml);
	char *command_line = g_strconcat ("ghemical -f ", tmpname, NULL);
	g_free (tmpname);
	g_spawn_command_line_async (command_line, NULL);
	g_free (command_line);
}
