agg_clean_or_dirty()
{
	int acod_rc = FSCK_OK;

	if (!agg_recptr->ag_dirty) {


		fsck_send_msg(fsck_AGGCLN);

		if (agg_recptr->processing_readonly) {

			if ((sb_ptr->s_state & FM_DIRTY) == FM_DIRTY) {

				fsck_send_msg(fsck_AGGCLNNOTDRTY);
			}
		} else {

			fsck_send_msg(fsck_ALLFXD);
			sb_ptr->s_state = FM_CLEAN;
			acod_rc = replicate_superblock();
			if (acod_rc == FSCK_OK) {
				fsck_send_msg(fsck_AGGMRKDCLN);
			}
		}
	} else {

		fsck_send_msg(fsck_AGGDRTY);

		if ((sb_ptr->s_state & FM_DIRTY) != FM_DIRTY) {

			if (agg_recptr->processing_readonly) {

				fsck_send_msg(fsck_AGGDRTYNOTCLN, Vol_Label);
			} else {


				sb_ptr->s_state = FM_DIRTY;
				acod_rc = replicate_superblock();
				if (acod_rc == FSCK_OK) {
					fsck_send_msg(fsck_AGGMRKDDRTY);
				}
			}
		}
	}

	return (acod_rc);
}
