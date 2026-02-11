ivtv_s_std_dec(struct ivtv *itv, v4l2_std_id std)
{
	struct yuv_playback_info *yi = &itv->yuv_info;
	DEFINE_WAIT(wait);
	int f;


	itv->std_out = std;
	itv->is_out_60hz = (std & V4L2_STD_525_60) ? 1 : 0;
	itv->is_out_50hz = !itv->is_out_60hz;
	ivtv_call_all(itv, video, s_std_output, itv->std_out);


	mutex_unlock(&itv->serialize_lock);
	for (f = 0; f < 4; f++) {
		prepare_to_wait(&itv->vsync_waitq, &wait,
				TASK_UNINTERRUPTIBLE);
		if ((read_reg(IVTV_REG_DEC_LINE_FIELD) >> 16) < 100)
			break;
		schedule_timeout(msecs_to_jiffies(25));
	}
	finish_wait(&itv->vsync_waitq, &wait);
	mutex_lock(&itv->serialize_lock);

	if (f == 4)
		IVTV_WARN("Mode change failed to sync to decoder\n");

	ivtv_vapi(itv, CX2341X_DEC_SET_STANDARD, 1, itv->is_out_50hz);
	itv->main_rect.left = 0;
	itv->main_rect.top = 0;
	itv->main_rect.width = 720;
	itv->main_rect.height = itv->is_out_50hz ? 576 : 480;
	ivtv_vapi(itv, CX2341X_OSD_SET_FRAMEBUFFER_WINDOW, 4,
		720, itv->main_rect.height, 0, 0);
	yi->main_rect = itv->main_rect;
	if (!itv->osd_info) {
		yi->osd_full_w = 720;
		yi->osd_full_h = itv->is_out_50hz ? 576 : 480;
	}
}
