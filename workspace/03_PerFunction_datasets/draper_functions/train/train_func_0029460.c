solo_enc_g_std(struct file *file, void *priv, v4l2_std_id *i)
{
	struct solo_enc_dev *solo_enc = video_drvdata(file);
	struct solo_dev *solo_dev = solo_enc->solo_dev;

	if (solo_dev->video_type == SOLO_VO_FMT_TYPE_NTSC)
		*i = V4L2_STD_NTSC_M;
	else
		*i = V4L2_STD_PAL;
	return 0;
}
