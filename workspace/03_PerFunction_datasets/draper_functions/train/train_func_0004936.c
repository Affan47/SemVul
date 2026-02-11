ivtv_yuv_work_handler(struct ivtv *itv)
{
	struct yuv_playback_info *yi = &itv->yuv_info;
	struct yuv_frame_info f;
	int frame = yi->update_frame;
	u32 yuv_update;

	IVTV_DEBUG_YUV("Update yuv registers for frame %d\n", frame);
	f = yi->new_frame_info[frame];

	if (yi->track_osd) {

		f.pan_x = yi->osd_x_pan;
		f.pan_y = yi->osd_y_pan;
		f.vis_w = yi->osd_vis_w;
		f.vis_h = yi->osd_vis_h;
	} else {

		f.pan_x = 0;
		f.pan_y = 0;
		f.vis_w = 720;
		f.vis_h = yi->decode_height;
	}


	if (!(yuv_update = ivtv_yuv_window_setup(itv, &f)))
		return;

	if (yuv_update & IVTV_YUV_UPDATE_INVALID) {
		write_reg(0x01008080, 0x2898);
	} else if (yuv_update) {
		write_reg(0x00108080, 0x2898);

		if (yuv_update & IVTV_YUV_UPDATE_HORIZONTAL)
			ivtv_yuv_handle_horizontal(itv, &f);

		if (yuv_update & IVTV_YUV_UPDATE_VERTICAL)
			ivtv_yuv_handle_vertical(itv, &f);
	}
	yi->old_frame_info = f;
}
