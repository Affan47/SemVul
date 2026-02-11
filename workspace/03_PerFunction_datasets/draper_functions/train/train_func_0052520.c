v4l2_needs_conversion(int index)
{
	if (devices[index].convert == NULL)
		return 0;

	return v4lconvert_needs_conversion(devices[index].convert,
			&devices[index].src_fmt, &devices[index].dest_fmt);
}
