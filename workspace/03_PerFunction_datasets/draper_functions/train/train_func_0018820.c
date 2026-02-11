vivid_start_generating_vid_out(struct vivid_dev *dev, bool *pstreaming)
{
	dprintk(dev, 1, "%s\n", __func__);

	if (dev->kthread_vid_out) {
		u32 seq_count = dev->out_seq_count + dev->seq_wrap * 128;

		if (pstreaming == &dev->vid_out_streaming)
			dev->vid_out_seq_start = seq_count;
		else
			dev->vbi_out_seq_start = seq_count;
		*pstreaming = true;
		return 0;
	}


	dev->jiffies_vid_out = jiffies;
	dev->vid_out_seq_start = dev->seq_wrap * 128;
	dev->vbi_out_seq_start = dev->seq_wrap * 128;

	dev->kthread_vid_out = kthread_run(vivid_thread_vid_out, dev,
			"%s-vid-out", dev->v4l2_dev.name);

	if (IS_ERR(dev->kthread_vid_out)) {
		v4l2_err(&dev->v4l2_dev, "kernel_thread() failed\n");
		return PTR_ERR(dev->kthread_vid_out);
	}
	*pstreaming = true;
	vivid_grab_controls(dev, true);

	dprintk(dev, 1, "returning from %s\n", __func__);
	return 0;
}
