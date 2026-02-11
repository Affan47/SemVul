validate_ACL(struct dinode *inoptr, uint32_t inoidx,
		 struct fsck_inode_record *inorecptr,
		 struct fsck_ino_msg_info *msg_info_ptr)
{
	int vacl_rc = FSCK_OK;
	dxd_t *dxd_ptr;
	uint32_t recorded_length, shortest_valid, longest_valid;
	uint32_t ext_length;
	int64_t ext_address;
	int8_t extent_is_valid = 0;
	uint16_t size16;
	struct dinode an_inode;

	dxd_ptr = &(inoptr->di_acl);
	msg_info_ptr->msg_dxdtyp = fsck_ACL;

	if (dxd_ptr->flag == 0)
		goto out;


	if ((dxd_ptr->flag != DXD_EXTENT) && (dxd_ptr->flag != DXD_INLINE)
	    && (dxd_ptr->flag != DXD_CORRUPT)) {


		fsck_send_msg(fsck_BADINODXDFLDD,
			      fsck_ref_msg(msg_info_ptr->msg_inotyp),
			      fsck_ref_msg(msg_info_ptr->msg_inopfx),
			      msg_info_ptr->msg_inonum,
			      fsck_ref_msg(msg_info_ptr->msg_dxdtyp));
		inorecptr->clr_acl_fld = 1;
		inorecptr->ignore_acl_blks = 1;
		agg_recptr->corrections_needed = 1;

		goto out;
	}

	if (dxd_ptr->flag == DXD_INLINE) {

		size16 = sizeof (an_inode.di_inlineea);
		agg_recptr->this_inode.acl_inline = 1;
		agg_recptr->this_inode.inline_acl_length =
		    (uint16_t) dxd_ptr->size;
		agg_recptr->this_inode.inline_acl_offset =
		    (uint16_t) addressDXD(dxd_ptr);

		if ((dxd_ptr->size == 0)
		    || (dxd_ptr->size >
			(size16 - agg_recptr->this_inode.inline_acl_offset))) {


			fsck_send_msg(fsck_BADINODXDFLDL,
				      fsck_ref_msg(msg_info_ptr->msg_inotyp),
				      fsck_ref_msg(msg_info_ptr->msg_inopfx),
				      msg_info_ptr->msg_inonum,
				      fsck_ref_msg(msg_info_ptr->msg_dxdtyp));

			inorecptr->clr_acl_fld = 1;
			agg_recptr->corrections_needed = 1;
		}
	} else if (dxd_ptr->flag == DXD_EXTENT) {

		ext_length = lengthDXD(dxd_ptr);
		shortest_valid = (ext_length - 1) * sb_ptr->s_bsize + 1;
		longest_valid = ext_length * sb_ptr->s_bsize;
		if ((ext_length == 0) || (dxd_ptr->size < shortest_valid)
		    || (dxd_ptr->size > longest_valid)) {

			fsck_send_msg(fsck_BADINODXDFLDL,
				      fsck_ref_msg(msg_info_ptr->msg_inotyp),
				      fsck_ref_msg(msg_info_ptr->msg_inopfx),
				      msg_info_ptr->msg_inonum,
				      fsck_ref_msg(msg_info_ptr->msg_dxdtyp));

			inorecptr->clr_acl_fld = 1;
			inorecptr->ignore_acl_blks = 1;
			agg_recptr->corrections_needed = 1;
			recorded_length = 0;
			extent_is_valid = 0;
		} else {

			agg_recptr->this_inode.acl_blks = ext_length;
			ext_address = addressDXD(dxd_ptr);
			vacl_rc =
			    process_extent(inorecptr, ext_length, ext_address,
					   0, -1, msg_info_ptr,
					   &recorded_length, &extent_is_valid,
					   FSCK_RECORD_DUPCHECK);


			agg_recptr->blocks_this_fset += recorded_length;
			agg_recptr->this_inode.all_blks += recorded_length;
		}

		if (!extent_is_valid) {
			inorecptr->clr_acl_fld = 1;
			agg_recptr->corrections_needed = 1;
		}
	}
      out:
	return (vacl_rc);
}
