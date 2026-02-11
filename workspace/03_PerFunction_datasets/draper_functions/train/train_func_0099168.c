cx2341x_ctrl_get_menu(const struct cx2341x_mpeg_params *p, u32 id)
{
	static const char * const mpeg_stream_type_without_ts[] = {
		"MPEG-2 Program Stream",
		"",
		"MPEG-1 System Stream",
		"MPEG-2 DVD-compatible Stream",
		"MPEG-1 VCD-compatible Stream",
		"MPEG-2 SVCD-compatible Stream",
		NULL
	};

	static const char *mpeg_stream_type_with_ts[] = {
		"MPEG-2 Program Stream",
		"MPEG-2 Transport Stream",
		"MPEG-1 System Stream",
		"MPEG-2 DVD-compatible Stream",
		"MPEG-1 VCD-compatible Stream",
		"MPEG-2 SVCD-compatible Stream",
		NULL
	};

	static const char *mpeg_audio_encoding_l2_ac3[] = {
		"",
		"MPEG-1/2 Layer II",
		"",
		"",
		"AC-3",
		NULL
	};

	switch (id) {
	case V4L2_CID_MPEG_STREAM_TYPE:
		return (p->capabilities & CX2341X_CAP_HAS_TS) ?
			mpeg_stream_type_with_ts : mpeg_stream_type_without_ts;
	case V4L2_CID_MPEG_AUDIO_ENCODING:
		return (p->capabilities & CX2341X_CAP_HAS_AC3) ?
			mpeg_audio_encoding_l2_ac3 : v4l2_ctrl_get_menu(id);
	case V4L2_CID_MPEG_AUDIO_L1_BITRATE:
	case V4L2_CID_MPEG_AUDIO_L3_BITRATE:
		return NULL;
	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		return cx2341x_get_menu(id);
	default:
		return v4l2_ctrl_get_menu(id);
	}
}
