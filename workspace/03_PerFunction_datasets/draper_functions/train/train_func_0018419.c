sd_pkt_scan_bayer(struct gspca_dev *gspca_dev, u8 *data, int len)
{
	struct cam *cam = &gspca_dev->cam;
	int imagesize = cam->cam_mode[gspca_dev->curr_mode].sizeimage;

	if (gspca_dev->image_len == 0) {
		gspca_frame_add(gspca_dev, FIRST_PACKET, data, len);
		return;
	}

	if (gspca_dev->image_len + len >= imagesize) {
		sd_complete_frame(gspca_dev, data, len);
		return;
	}

	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}
