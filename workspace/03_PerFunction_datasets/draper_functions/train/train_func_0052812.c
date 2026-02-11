jl2005c_stream_start_cif_small(struct gspca_dev *gspca_dev)
{
	int i;
	int retval = -1;
	static u8 instruction[][2] = {
		{0x06, 0x00},
		{0x7c, 0x00},
		{0x7d, 0x32},
		{0x02, 0x00},
		{0x01, 0x00},
		{0x04, 0x42},
	};

	for (i = 0; i < ARRAY_SIZE(instruction); i++) {
		msleep(60);
		retval = jl2005c_write2(gspca_dev, instruction[i]);
		if (retval < 0)
			return retval;
	}
	msleep(60);
	return retval;
}
