recv_synchronize_groups(

	log_group_t*	up_to_date_group)

{
	log_group_t*	group;
	ib_uint64_t	start_lsn;
	ib_uint64_t	end_lsn;
	ib_uint64_t	recovered_lsn;

	recovered_lsn = recv_sys->recovered_lsn;


	start_lsn = ut_uint64_align_down(recovered_lsn,
					 OS_FILE_LOG_BLOCK_SIZE);
	end_lsn = ut_uint64_align_up(recovered_lsn, OS_FILE_LOG_BLOCK_SIZE);

	ut_a(start_lsn != end_lsn);

	log_group_read_log_seg(LOG_RECOVER, recv_sys->last_block,
			       up_to_date_group, start_lsn, end_lsn);

	group = UT_LIST_GET_FIRST(log_sys->log_groups);

	while (group) {
		if (group != up_to_date_group) {


			recv_copy_group(group, up_to_date_group,
					recovered_lsn);
		}


		log_group_set_fields(group, recovered_lsn);

		group = UT_LIST_GET_NEXT(log_groups, group);
	}


	log_groups_write_checkpoint_info();

	mutex_exit(&(log_sys->mutex));


	rw_lock_s_lock(&(log_sys->checkpoint_lock));
	rw_lock_s_unlock(&(log_sys->checkpoint_lock));

	mutex_enter(&(log_sys->mutex));
}
