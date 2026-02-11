zoran_enum_output(struct file *file, void *__fh,
				  struct v4l2_output *outp)
{
	if (outp->index != 0)
		return -EINVAL;

	outp->index = 0;
	outp->type = V4L2_OUTPUT_TYPE_ANALOGVGAOVERLAY;
	strncpy(outp->name, "Autodetect", sizeof(outp->name)-1);

	return 0;
}
