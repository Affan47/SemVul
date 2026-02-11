SV_BeginDemoserver (void)
{
	char		name[MAX_OSPATH];

	Com_sprintf (name, sizeof(name), "demos/%s", sv.name);
	FS_FOpenFile (name, &sv.demofile);
	if (!sv.demofile)
		Com_Error (ERR_DROP, "Couldn't open %s\n", name);
	sv.demo_ofs = 0;
	sv.demosize = FS_LoadFile (name, (void **)&sv.demobuf);
}
