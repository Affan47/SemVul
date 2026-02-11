bttv_switch_type(struct bttv_fh *fh, enum v4l2_buf_type type)
{
	struct videobuf_queue *q = bttv_queue(fh);
	int res = bttv_resource(fh);

	if (check_btres(fh,res))
		return -EBUSY;
	if (videobuf_queue_is_busy(q))
		return -EBUSY;
	fh->type = type;
	return 0;
}
