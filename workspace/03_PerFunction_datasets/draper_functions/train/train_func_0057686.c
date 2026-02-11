del_from_work_list(struct super_block *s,
			       struct reiserfs_journal_list *jl)
{
	struct reiserfs_journal *journal = SB_JOURNAL(s);
	if (!list_empty(&jl->j_working_list)) {
		list_del_init(&jl->j_working_list);
		journal->j_num_work_lists--;
	}
}
