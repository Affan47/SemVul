ocfs2_info_handle_maxslots(struct inode *inode,
				      struct ocfs2_info_request __user *req)
{
	struct ocfs2_info_maxslots oim;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	if (o2info_from_user(oim, req))
		return -EFAULT;

	oim.im_max_slots = osb->max_slots;

	o2info_set_request_filled(&oim.im_req);

	if (o2info_to_user(oim, req))
		return -EFAULT;

	return 0;
}
