ocfs2_dlm_seq_show(struct seq_file *m, void *v)
{
	int i;
	char *lvb;
	struct ocfs2_lock_res *lockres = v;

	if (!lockres)
		return -EINVAL;

	seq_printf(m, "0x%x\t", OCFS2_DLM_DEBUG_STR_VERSION);

	if (lockres->l_type == OCFS2_LOCK_TYPE_DENTRY)
		seq_printf(m, "%.*s%08x\t", OCFS2_DENTRY_LOCK_INO_START - 1,
			   lockres->l_name,
			   (unsigned int)ocfs2_get_dentry_lock_ino(lockres));
	else
		seq_printf(m, "%.*s\t", OCFS2_LOCK_ID_MAX_LEN, lockres->l_name);

	seq_printf(m, "%d\t"
		   "0x%lx\t"
		   "0x%x\t"
		   "0x%x\t"
		   "%u\t"
		   "%u\t"
		   "%d\t"
		   "%d\t",
		   lockres->l_level,
		   lockres->l_flags,
		   lockres->l_action,
		   lockres->l_unlock_action,
		   lockres->l_ro_holders,
		   lockres->l_ex_holders,
		   lockres->l_requested,
		   lockres->l_blocking);


	lvb = ocfs2_dlm_lvb(&lockres->l_lksb);
	for(i = 0; i < DLM_LVB_LEN; i++)
		seq_printf(m, "0x%x\t", lvb[i]);

#ifdef CONFIG_OCFS2_FS_STATS
# define lock_num_prmode(_l)		((_l)->l_lock_prmode.ls_gets)
# define lock_num_exmode(_l)		((_l)->l_lock_exmode.ls_gets)
# define lock_num_prmode_failed(_l)	((_l)->l_lock_prmode.ls_fail)
# define lock_num_exmode_failed(_l)	((_l)->l_lock_exmode.ls_fail)
# define lock_total_prmode(_l)		((_l)->l_lock_prmode.ls_total)
# define lock_total_exmode(_l)		((_l)->l_lock_exmode.ls_total)
# define lock_max_prmode(_l)		((_l)->l_lock_prmode.ls_max)
# define lock_max_exmode(_l)		((_l)->l_lock_exmode.ls_max)
# define lock_refresh(_l)		((_l)->l_lock_refresh)
#else
# define lock_num_prmode(_l)		(0)
# define lock_num_exmode(_l)		(0)
# define lock_num_prmode_failed(_l)	(0)
# define lock_num_exmode_failed(_l)	(0)
# define lock_total_prmode(_l)		(0ULL)
# define lock_total_exmode(_l)		(0ULL)
# define lock_max_prmode(_l)		(0)
# define lock_max_exmode(_l)		(0)
# define lock_refresh(_l)		(0)
#endif

	seq_printf(m, "%u\t"
		   "%u\t"
		   "%u\t"
		   "%u\t"
		   "%llu\t"
		   "%llu\t"
		   "%u\t"
		   "%u\t"
		   "%u\t",
		   lock_num_prmode(lockres),
		   lock_num_exmode(lockres),
		   lock_num_prmode_failed(lockres),
		   lock_num_exmode_failed(lockres),
		   lock_total_prmode(lockres),
		   lock_total_exmode(lockres),
		   lock_max_prmode(lockres),
		   lock_max_exmode(lockres),
		   lock_refresh(lockres));


	seq_printf(m, "\n");
	return 0;
}
