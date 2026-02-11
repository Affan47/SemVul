reg_w_array(struct gspca_dev *gspca_dev,
			const u8 (*data)[2], int len)
{
	while (--len >= 0) {
		reg_w(gspca_dev, (*data)[0], (*data)[1]);
		data++;
	}
}
