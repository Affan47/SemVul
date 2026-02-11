go7007_start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct go7007 *go = vb2_get_drv_priv(q);
	int ret;

	set_formatting(go);
	mutex_lock(&go->hw_lock);
	go->next_seq = 0;
	go->active_buf = NULL;
	go->modet_event_status = 0;
	q->streaming = 1;
	if (go7007_start_encoder(go) < 0)
		ret = -EIO;
	else
		ret = 0;
	mutex_unlock(&go->hw_lock);
	if (ret) {
		q->streaming = 0;
		return ret;
	}
	call_all(&go->v4l2_dev, video, s_stream, 1);
	v4l2_ctrl_grab(go->mpeg_video_gop_size, true);
	v4l2_ctrl_grab(go->mpeg_video_gop_closure, true);
	v4l2_ctrl_grab(go->mpeg_video_bitrate, true);
	v4l2_ctrl_grab(go->mpeg_video_aspect_ratio, true);

	if (go->board_id == GO7007_BOARDID_ADS_USBAV_709)
		go7007_write_addr(go, 0x3c82, 0x0005);
	return ret;
}
