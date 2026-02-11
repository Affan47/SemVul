vpx3220_s_std(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct vpx3220 *decoder = to_vpx3220(sd);
	int temp_input;


	temp_input = vpx3220_fp_read(sd, 0xf2);

	v4l2_dbg(1, debug, sd, "s_std %llx\n", (unsigned long long)std);
	if (std & V4L2_STD_NTSC) {
		vpx3220_write_fp_block(sd, init_ntsc, sizeof(init_ntsc) >> 1);
		v4l2_dbg(1, debug, sd, "norm switched to NTSC\n");
	} else if (std & V4L2_STD_PAL) {
		vpx3220_write_fp_block(sd, init_pal, sizeof(init_pal) >> 1);
		v4l2_dbg(1, debug, sd, "norm switched to PAL\n");
	} else if (std & V4L2_STD_SECAM) {
		vpx3220_write_fp_block(sd, init_secam, sizeof(init_secam) >> 1);
		v4l2_dbg(1, debug, sd, "norm switched to SECAM\n");
	} else {
		return -EINVAL;
	}

	decoder->norm = std;


	vpx3220_fp_write(sd, 0xf2, temp_input | 0x0010);
	udelay(10);
	return 0;
}
