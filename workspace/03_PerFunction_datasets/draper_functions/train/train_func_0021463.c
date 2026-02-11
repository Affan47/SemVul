vmw_overlay_stop(struct vmw_private *dev_priv,
			    uint32_t stream_id, bool pause,
			    bool interruptible)
{
	struct vmw_overlay *overlay = dev_priv->overlay_priv;
	struct vmw_stream *stream = &overlay->stream[stream_id];
	int ret;


	if (!stream->buf)
		return 0;


	if (!stream->paused) {
		ret = vmw_overlay_send_stop(dev_priv, stream_id,
					    interruptible);
		if (ret)
			return ret;


		ret = vmw_overlay_move_buffer(dev_priv, stream->buf, false,
					      interruptible);
		if (interruptible && ret == -ERESTARTSYS)
			return ret;
		else
			BUG_ON(ret != 0);
	}

	if (!pause) {
		vmw_dmabuf_unreference(&stream->buf);
		stream->paused = false;
	} else {
		stream->paused = true;
	}

	return 0;
}
