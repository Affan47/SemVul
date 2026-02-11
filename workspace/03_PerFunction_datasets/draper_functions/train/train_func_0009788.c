m5mols_get_frame_desc(struct v4l2_subdev *sd, unsigned int pad,
				 struct v4l2_mbus_frame_desc *fd)
{
	struct m5mols_info *info = to_m5mols(sd);

	if (pad != 0 || fd == NULL)
		return -EINVAL;

	mutex_lock(&info->lock);


	fd->entry[0].length = info->cap.buf_size;
	fd->entry[0].pixelcode = info->ffmt[M5MOLS_RESTYPE_CAPTURE].code;
	mutex_unlock(&info->lock);

	fd->entry[0].flags = V4L2_MBUS_FRAME_DESC_FL_LEN_MAX;
	fd->num_entries = 1;

	return 0;
}
