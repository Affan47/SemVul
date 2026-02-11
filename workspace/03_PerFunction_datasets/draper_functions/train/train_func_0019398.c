sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,
			int len)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i;
	static __u8 ffd9[] = {0xff, 0xd9};


	if (data[0] == 0xff) {
		if (data[1] != 0x01) {

			return;
		}
		gspca_frame_add(gspca_dev, LAST_PACKET,
					ffd9, 2);


		gspca_frame_add(gspca_dev, FIRST_PACKET,
			sd->jpeg_hdr, JPEG_HDR_SZ);

		data += SPCA500_OFFSET_DATA;
		len -= SPCA500_OFFSET_DATA;
	} else {
		data += 1;
		len -= 1;
	}


	i = 0;
	do {
		if (data[i] == 0xff) {
			gspca_frame_add(gspca_dev, INTER_PACKET,
					data, i + 1);
			len -= i;
			data += i;
			*data = 0x00;
			i = 0;
		}
		i++;
	} while (i < len);
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}
