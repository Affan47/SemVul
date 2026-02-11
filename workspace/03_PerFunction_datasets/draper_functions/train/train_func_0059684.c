mxr_dqbuf(struct file *file, void *priv, struct v4l2_buffer *p)
{
	struct mxr_layer *layer = video_drvdata(file);

	mxr_dbg(layer->mdev, "%s:%d\n", __func__, __LINE__);
	return vb2_dqbuf(&layer->vb_queue, p, file->f_flags & O_NONBLOCK);
}
