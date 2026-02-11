cfg_file_update_ptr(char *str)
{
	char	*newstr;
	int	len;

	len = strlen(str) + 1;
	newstr = malloc(len);
	memcpy(newstr, str, len);
	if(g_cfg_file_strptr) {
		if(*g_cfg_file_strptr) {
			free(*g_cfg_file_strptr);
		}
	}
	*g_cfg_file_strptr = newstr;
	if(g_cfg_file_strptr == &(g_cfg_rom_path)) {
		printf("Updated ROM file\n");
		load_roms_init_memory();
	}
	g_config_kegs_update_needed = 1;
}
