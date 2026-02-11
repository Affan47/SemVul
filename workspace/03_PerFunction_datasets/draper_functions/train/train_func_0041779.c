vivid_start_generating_vid_cap(struct vivid_dev *dev, bool *pstreaming)
{
	dprintk(dev, 1, "%s\n", __func__);

	if (dev->kthread_vid_cap) {
		u32 seq_count = dev->cap_seq_count + dev->seq_wrap * 128;

		if (pstreaming == &dev->vid_cap_streaming)
			dev->vid_cap_seq_start = seq_count;
		else
			dev->vbi_cap_seq_start = seq_count;
		*pstreaming = true;
		return 0;
	}


	tpg_init_mv_count(&dev->tpg);

	dev->vid_cap_seq_start = dev->seq_wrap * 128;
	dev->vbi_cap_seq_start = dev->seq_wrap * 128;

	dev->kthread_vid_cap = kthread_run(vivid_thread_vid_cap, dev,
			"%s-vid-cap", dev->v4l2_dev.name);

	if (IS_ERR(dev->kthread_vid_cap)) {
		v4l2_err(&dev->v4l2_dev, "kernel_thread() failed\n");
		return PTR_ERR(dev->kthread_vid_cap);
	}
	*pstreaming = true;
	vivid_grab_controls(dev, true);

	dprintk(dev, 1, "returning from %s\n", __func__);
	return 0;
}
