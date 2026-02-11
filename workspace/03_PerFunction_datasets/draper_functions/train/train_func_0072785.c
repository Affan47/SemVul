log_group_checkpoint(

	log_group_t*	group)
{
	log_group_t*	group2;
#ifdef UNIV_LOG_ARCHIVE
	ib_uint64_t	archived_lsn;
	ib_uint64_t	next_archived_lsn;
#endif
	ulint		write_offset;
	ulint		fold;
	byte*		buf;
	ulint		i;

	ut_ad(mutex_own(&(log_sys->mutex)));
#if LOG_CHECKPOINT_SIZE > OS_FILE_LOG_BLOCK_SIZE
# error "LOG_CHECKPOINT_SIZE > OS_FILE_LOG_BLOCK_SIZE"
#endif

	buf = group->checkpoint_buf;

	mach_write_to_8(buf + LOG_CHECKPOINT_NO, log_sys->next_checkpoint_no);
	mach_write_to_8(buf + LOG_CHECKPOINT_LSN, log_sys->next_checkpoint_lsn);

	mach_write_to_4(buf + LOG_CHECKPOINT_OFFSET,
			log_group_calc_lsn_offset(
				log_sys->next_checkpoint_lsn, group));

	mach_write_to_4(buf + LOG_CHECKPOINT_LOG_BUF_SIZE, log_sys->buf_size);

#ifdef UNIV_LOG_ARCHIVE
	if (log_sys->archiving_state == LOG_ARCH_OFF) {
		archived_lsn = IB_ULONGLONG_MAX;
	} else {
		archived_lsn = log_sys->archived_lsn;

		if (archived_lsn != log_sys->next_archived_lsn) {
			next_archived_lsn = log_sys->next_archived_lsn;

		}
	}

	mach_write_to_8(buf + LOG_CHECKPOINT_ARCHIVED_LSN, archived_lsn);
#else
	mach_write_to_8(buf + LOG_CHECKPOINT_ARCHIVED_LSN, IB_ULONGLONG_MAX);
#endif

	for (i = 0; i < LOG_MAX_N_GROUPS; i++) {
		log_checkpoint_set_nth_group_info(buf, i, 0, 0);
	}

	group2 = UT_LIST_GET_FIRST(log_sys->log_groups);

	while (group2) {
		log_checkpoint_set_nth_group_info(buf, group2->id,
#ifdef UNIV_LOG_ARCHIVE
						  group2->archived_file_no,
						  group2->archived_offset
#else
						  0, 0
#endif
						  );

		group2 = UT_LIST_GET_NEXT(log_groups, group2);
	}

	fold = ut_fold_binary(buf, LOG_CHECKPOINT_CHECKSUM_1);
	mach_write_to_4(buf + LOG_CHECKPOINT_CHECKSUM_1, fold);

	fold = ut_fold_binary(buf + LOG_CHECKPOINT_LSN,
			      LOG_CHECKPOINT_CHECKSUM_2 - LOG_CHECKPOINT_LSN);
	mach_write_to_4(buf + LOG_CHECKPOINT_CHECKSUM_2, fold);


	mach_write_to_4(buf + LOG_CHECKPOINT_FSP_FREE_LIMIT,
			log_fsp_current_free_limit);

	mach_write_to_4(buf + LOG_CHECKPOINT_FSP_MAGIC_N,
			LOG_CHECKPOINT_FSP_MAGIC_N_VAL);


	if ((log_sys->next_checkpoint_no & 1) == 0) {
		write_offset = LOG_CHECKPOINT_1;
	} else {
		write_offset = LOG_CHECKPOINT_2;
	}

	if (log_do_write) {
		if (log_sys->n_pending_checkpoint_writes == 0) {

			rw_lock_x_lock_gen(&(log_sys->checkpoint_lock),
					   LOG_CHECKPOINT);
		}

		log_sys->n_pending_checkpoint_writes++;

		log_sys->n_log_ios++;


		fil_io(OS_FILE_WRITE | OS_FILE_LOG, FALSE, group->space_id, 0,
		       write_offset / UNIV_PAGE_SIZE,
		       write_offset % UNIV_PAGE_SIZE,
		       OS_FILE_LOG_BLOCK_SIZE,
		       buf, ((byte*)group + 1));

		ut_ad(((ulint)group & 0x1UL) == 0);
	}
}
