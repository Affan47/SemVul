start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct mxr_layer *layer = vb2_get_drv_priv(vq);
	struct mxr_device *mdev = layer->mdev;
	unsigned long flags;

	mxr_dbg(mdev, "%s\n", __func__);


	mxr_output_get(mdev);

	mxr_layer_update_output(layer);
	layer->ops.format_set(layer);

	spin_lock_irqsave(&layer->enq_slock, flags);
	layer->state = MXR_LAYER_STREAMING;
	spin_unlock_irqrestore(&layer->enq_slock, flags);

	layer->ops.stream_set(layer, MXR_ENABLE);
	mxr_streamer_get(mdev);

	return 0;
}
