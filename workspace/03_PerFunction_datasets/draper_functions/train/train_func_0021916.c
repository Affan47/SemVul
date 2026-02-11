set_video_mode_Kiara(struct pwc_device *pdev, int size, int pixfmt,
				int frames, int *compression, int send_to_cam)
{
	const struct Kiara_table_entry *pChoose = NULL;
	int fps, ret = 0;

	if (size >= PSZ_MAX || *compression < 0 || *compression > 3)
		return -EINVAL;
	if (frames < 5)
		frames = 5;
	else if (size == PSZ_VGA && frames > 15)
		frames = 15;
	else if (frames > 30)
		frames = 30;
	fps = (frames / 5) - 1;


	while (*compression <= 3) {
		pChoose = &Kiara_table[size][fps][*compression];
		if (pChoose->alternate != 0)
			break;
		(*compression)++;
	}
	if (pChoose == NULL || pChoose->alternate == 0)
		return -ENOENT;


	if (send_to_cam)
		ret = send_video_command(pdev, 4, pChoose->mode, 12);
	if (ret < 0)
		return ret;

	if (pChoose->bandlength > 0 && pixfmt == V4L2_PIX_FMT_YUV420)
		pwc_dec23_init(pdev, pChoose->mode);


	pdev->pixfmt = pixfmt;
	pdev->vframes = (fps + 1) * 5;
	pdev->valternate = pChoose->alternate;
	pdev->width  = pwc_image_sizes[size][0];
	pdev->height = pwc_image_sizes[size][1];
	pdev->vbandlength = pChoose->bandlength;
	if (pdev->vbandlength > 0)
		pdev->frame_size = (pdev->vbandlength * pdev->height) / 4;
	else
		pdev->frame_size = (pdev->width * pdev->height * 12) / 8;
	PWC_TRACE("frame_size=%d, vframes=%d, vsize=%d, vbandlength=%d\n",
	    pdev->frame_size, pdev->vframes, size, pdev->vbandlength);
	return 0;
}
