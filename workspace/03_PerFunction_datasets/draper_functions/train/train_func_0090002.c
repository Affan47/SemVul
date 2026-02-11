setup_fs_interface(void)
    {
#ifdef WIN32
	uid = 0;
#else
	uid = getuid();
#endif
	if (!get_fsusage && !_GK.client_mode && gkrellm_sys_fs_init())
		{
		get_fsusage = gkrellm_sys_fs_get_fsusage;
		get_mounts_list = gkrellm_sys_fs_get_mounts_list;
		get_fstab_list = gkrellm_sys_fs_get_fstab_list;
		get_fstab_modified = gkrellm_sys_fs_fstab_modified;
		}
	return get_fsusage ? TRUE : FALSE;
	}
