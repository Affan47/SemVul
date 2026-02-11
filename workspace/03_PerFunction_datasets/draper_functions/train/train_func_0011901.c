cit_set_hue(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->model) {
	case CIT_MODEL0:
	case CIT_MODEL1:
	case CIT_IBM_NETCAM_PRO:

		break;
	case CIT_MODEL2:
		cit_model2_Packet1(gspca_dev, 0x0024, val);

		break;
	case CIT_MODEL3: {


		if (0) {

			int i = 0x05 + val * 1000 / 2540;
			cit_model3_Packet1(gspca_dev, 0x007e, i);
		}
		break;
	}
	case CIT_MODEL4:


		cit_write_reg(gspca_dev, 0x00aa, 0x012d);
		cit_write_reg(gspca_dev, 0x001e, 0x012f);
		cit_write_reg(gspca_dev, 0xd141, 0x0124);
		cit_write_reg(gspca_dev,    160, 0x0127);
		cit_write_reg(gspca_dev,    160, 0x012e);
		cit_write_reg(gspca_dev,    160, 0x0130);
		cit_write_reg(gspca_dev, 0x8a28, 0x0124);
		cit_write_reg(gspca_dev, val, 0x012d);
		cit_write_reg(gspca_dev, 0xf545, 0x0124);
		break;
	}
	return 0;
}
