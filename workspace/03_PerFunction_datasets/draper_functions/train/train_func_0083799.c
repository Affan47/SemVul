mxr_mplane_fill(struct v4l2_plane_pix_format *planes,
	const struct mxr_format *fmt, u32 width, u32 height)
{
	int i;


	if (!planes)
		return;

	memset(planes, 0, sizeof(*planes) * fmt->num_subframes);
	for (i = 0; i < fmt->num_planes; ++i) {
		struct v4l2_plane_pix_format *plane = planes
			+ fmt->plane2subframe[i];
		const struct mxr_block *blk = &fmt->plane[i];
		u32 bl_width = divup(width, blk->width);
		u32 bl_height = divup(height, blk->height);
		u32 sizeimage = bl_width * bl_height * blk->size;
		u32 bytesperline = bl_width * blk->size / blk->height;

		plane->sizeimage += sizeimage;
		plane->bytesperline = max(plane->bytesperline, bytesperline);
	}
}
