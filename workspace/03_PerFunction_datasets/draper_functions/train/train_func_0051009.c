is_cur_manual(const struct v4l2_ctrl *master)
{
	return master->is_auto && master->cur.val == master->manual_mode_value;
}
