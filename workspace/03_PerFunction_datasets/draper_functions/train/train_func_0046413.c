viacam_set_scale(struct via_camera *cam)
{
	unsigned int avscale;
	int sf;

	if (cam->user_format.width == VGA_WIDTH)
		avscale = 0;
	else {
		sf = (cam->user_format.width*2048)/VGA_WIDTH;
		avscale = VCR_AVS_HEN | sf;
	}
	if (cam->user_format.height < VGA_HEIGHT) {
		sf = (1024*cam->user_format.height)/VGA_HEIGHT;
		avscale |= VCR_AVS_VEN | (sf << 16);
	}
	viacam_write_reg(cam, VCR_AVSCALE, avscale);
}
