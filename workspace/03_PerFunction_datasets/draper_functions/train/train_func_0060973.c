vidioc_g_jpegcomp(struct file *file, void *priv,
			 struct v4l2_jpegcompression *jc)
{
	struct s2255_vc *vc = video_drvdata(file);

	memset(jc, 0, sizeof(*jc));
	jc->quality = vc->jpegqual;
	dprintk(vc->dev, 2, "%s: quality %d\n", __func__, jc->quality);
	return 0;
}
