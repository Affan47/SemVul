misc_set(int fd)
{
	if (options[OptSetParm]) {
		memset(&parm, 0, sizeof(parm));
		parm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		parm.parm.capture.timeperframe.numerator = 1000;
		parm.parm.capture.timeperframe.denominator =
			fps * parm.parm.capture.timeperframe.numerator;

		if (doioctl(fd, VIDIOC_S_PARM, &parm) == 0) {
			struct v4l2_fract *tf = &parm.parm.capture.timeperframe;

			if (!tf->denominator || !tf->numerator)
				printf("Invalid frame rate\n");
			else
				printf("Frame rate set to %.3f fps\n",
					1.0 * tf->denominator / tf->numerator);
		}
	}

	if (options[OptSetOutputParm]) {
		memset(&parm, 0, sizeof(parm));
		parm.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		parm.parm.output.timeperframe.numerator = 1000;
		parm.parm.output.timeperframe.denominator =
			output_fps * parm.parm.output.timeperframe.numerator;

		if (doioctl(fd, VIDIOC_S_PARM, &parm) == 0) {
			struct v4l2_fract *tf = &parm.parm.output.timeperframe;

			if (!tf->denominator || !tf->numerator)
				printf("Invalid frame rate\n");
			else
				printf("Frame rate set to %.3f fps\n",
					1.0 * tf->denominator / tf->numerator);
		}
	}

	if (options[OptSetJpegComp]) {
		doioctl(fd, VIDIOC_S_JPEGCOMP, &jpegcomp);
	}

	if (options[OptEncoderCmd])
		doioctl(fd, VIDIOC_ENCODER_CMD, &enc_cmd);
	if (options[OptTryEncoderCmd])
		if (doioctl(fd, VIDIOC_TRY_ENCODER_CMD, &enc_cmd) == 0)
			print_enccmd(enc_cmd);
	if (options[OptDecoderCmd])
		doioctl(fd, VIDIOC_DECODER_CMD, &dec_cmd);
	if (options[OptTryDecoderCmd])
		if (doioctl(fd, VIDIOC_TRY_DECODER_CMD, &dec_cmd) == 0)
			print_deccmd(dec_cmd);
}
