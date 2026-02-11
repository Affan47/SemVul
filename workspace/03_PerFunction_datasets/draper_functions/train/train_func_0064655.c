count_inputs(int fd)
{
	struct v4l2_input input2;
	int i;
	for (i = 0;; i++) {
		memset(&input2, 0, sizeof(input2));
		input2.index = i;
		if (0 != v4l2_ioctl(fd, VIDIOC_ENUMINPUT, &input2))
			break;
		}
	return i;
}
