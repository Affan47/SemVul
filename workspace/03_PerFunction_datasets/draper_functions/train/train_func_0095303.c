stop_streaming(struct vb2_queue *vq)
{
	struct mxr_layer *layer = vb2_get_drv_priv(vq);
	struct mxr_device *mdev = layer->mdev;
	unsigned long flags;
	struct timer_list watchdog;
	struct mxr_buffer *buf, *buf_tmp;

	mxr_dbg(mdev, "%s\n", __func__);

	spin_lock_irqsave(&layer->enq_slock, flags);


	layer->state = MXR_LAYER_STREAMING_FINISH;


	list_for_each_entry_safe(buf, buf_tmp, &layer->enq_list, list) {
		list_del(&buf->list);
		vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	}

	spin_unlock_irqrestore(&layer->enq_slock, flags);


	setup_timer_on_stack(&watchdog, mxr_watchdog,
		(unsigned long)layer);
	mod_timer(&watchdog, jiffies + msecs_to_jiffies(1000));


	vb2_wait_for_all_buffers(vq);


	del_timer_sync(&watchdog);
	destroy_timer_on_stack(&watchdog);


	spin_lock_irqsave(&layer->enq_slock, flags);
	layer->state = MXR_LAYER_IDLE;
	spin_unlock_irqrestore(&layer->enq_slock, flags);


	layer->ops.stream_set(layer, MXR_DISABLE);

	mxr_streamer_put(mdev);

	mxr_output_put(mdev);
}
