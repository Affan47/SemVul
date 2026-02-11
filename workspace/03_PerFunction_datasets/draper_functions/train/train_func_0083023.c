viacam_fmt_pre(struct v4l2_pix_format *userfmt,
		struct v4l2_pix_format *sensorfmt)
{
	*sensorfmt = *userfmt;
	if (userfmt->width < QCIF_WIDTH || userfmt->height < QCIF_HEIGHT) {
		userfmt->width = QCIF_WIDTH;
		userfmt->height = QCIF_HEIGHT;
	}
	if (userfmt->width > VGA_WIDTH || userfmt->height > VGA_HEIGHT) {
		userfmt->width = VGA_WIDTH;
		userfmt->height = VGA_HEIGHT;
	}
	sensorfmt->width = VGA_WIDTH;
	sensorfmt->height = VGA_HEIGHT;
}
