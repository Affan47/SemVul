xTree_node_first_key(struct fsck_Xtree_info *xtiptr,
			 struct fsck_inode_record *inorecptr,
			 struct fsck_ino_msg_info *msg_info_ptr,
			 int desired_action)
{
	int xnfk_rc = FSCK_OK;


	if (xtiptr->this_Qel->node_first_offset &&
	    (xtiptr->this_key != xtiptr->this_Qel->node_first_offset)) {

		inorecptr->ignore_alloc_blks = 1;
		if (desired_action == FSCK_RECORD_DUPCHECK) {

			fsck_send_msg(fsck_BADKEYS,
				      fsck_ref_msg(msg_info_ptr->msg_inotyp),
				      fsck_ref_msg(msg_info_ptr->msg_inopfx),
				      msg_info_ptr->msg_inonum,
				      5);
		}
		goto out;
	}


	if (xtiptr->last_level != xtiptr->this_Qel->node_level)
		goto out;


	if ((xtiptr->dense_file) && (xtiptr->xtp_ptr->header.flag & BT_LEAF)) {

		if (xtiptr->this_key != (xtiptr->last_key + 1)) {

			inorecptr->ignore_alloc_blks = 1;
			if (desired_action == FSCK_RECORD_DUPCHECK) {

				fsck_send_msg(fsck_BADINOINTERNGAP,
					      fsck_ref_msg(msg_info_ptr->msg_inopfx),
					      msg_info_ptr->msg_inonum,
					      (long long) xtiptr->last_key);
			}
		}
	} else {

		if (xtiptr->this_key <= xtiptr->last_key) {

			inorecptr->ignore_alloc_blks = 1;
			if (desired_action == FSCK_RECORD_DUPCHECK) {

				fsck_send_msg(fsck_BADKEYS,
					      fsck_ref_msg(msg_info_ptr->msg_inotyp),
					      fsck_ref_msg(msg_info_ptr->msg_inopfx),
					      msg_info_ptr->msg_inonum, 6);
			}
		}
	}

      out:
	return (xnfk_rc);
}
