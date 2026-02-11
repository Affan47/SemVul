pvr2_hdw_v4l_get_minor_number(struct pvr2_hdw *hdw,
				  enum pvr2_v4l_type index)
{
	switch (index) {
	case pvr2_v4l_type_video: return hdw->v4l_minor_number_video;
	case pvr2_v4l_type_vbi: return hdw->v4l_minor_number_vbi;
	case pvr2_v4l_type_radio: return hdw->v4l_minor_number_radio;
	default: return -1;
	}
}
