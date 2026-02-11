mono_set_dirs (const char *assembly_dir, const char *config_dir)
{
	if (assembly_dir == NULL)
		assembly_dir = mono_config_get_assemblies_dir ();
	if (config_dir == NULL)
		config_dir = mono_config_get_cfg_dir ();
	mono_assembly_setrootdir (assembly_dir);
	mono_set_config_dir (config_dir);
}
