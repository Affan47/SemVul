sd_pkt_scan(struct gspca_dev *gspca_dev,
			__u8 *data,
			int len)
{
	unsigned char *sof;

	sof = sn9c2028_find_sof(gspca_dev, data, len);
	if (sof) {
		int n;


		n = sof - data;
		if (n > sizeof sn9c2028_sof_marker)
			n -= sizeof sn9c2028_sof_marker;
		else
			n = 0;
		gspca_frame_add(gspca_dev, LAST_PACKET, data, n);

		gspca_frame_add(gspca_dev, FIRST_PACKET,
			sn9c2028_sof_marker, sizeof sn9c2028_sof_marker);
		len -= sof - data;
		data = sof;
	}
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}
