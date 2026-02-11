sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,
			int len)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 *image;
	unsigned char *sof;

	sof = pac_find_sof(gspca_dev, &sd->sof_read, data, len);
	if (sof) {
		int n, lum_offset, footer_length;


		lum_offset = 24 + sizeof pac_sof_marker;
		footer_length = 26;


		n = (sof - data) - (footer_length + sizeof pac_sof_marker);
		if (n < 0) {
			gspca_dev->image_len += n;
			n = 0;
		} else {
			gspca_frame_add(gspca_dev, INTER_PACKET, data, n);
		}
		image = gspca_dev->image;
		if (image != NULL
		 && image[gspca_dev->image_len - 2] == 0xff
		 && image[gspca_dev->image_len - 1] == 0xd9)
			gspca_frame_add(gspca_dev, LAST_PACKET, NULL, 0);

		n = sof - data;
		len -= n;
		data = sof;


		if (gspca_dev->last_packet_type == LAST_PACKET &&
				n >= lum_offset)
			atomic_set(&sd->avg_lum, data[-lum_offset] +
						data[-lum_offset + 1]);
		else
			atomic_set(&sd->avg_lum, -1);


		pac_start_frame(gspca_dev,
			gspca_dev->pixfmt.height, gspca_dev->pixfmt.width);
	}
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}
