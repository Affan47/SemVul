cirrus_gen(struct cpssp *cpssp, struct sig_vga *video)
{
	unsigned int width, height;
	int pixel_format;
	unsigned long start_offset;
	unsigned int pitch;
	static int standingby = 0;

	_cirrus_get_resolution(cpssp, &width, &height);

	if ((cpssp->ext_power_management & 0x18) == 0x18) {

#ifdef CIRRUS_DEBUG_GEN
		faum_log(FAUM_LOG_DEBUG, __FUNCTION__, "", "STAND BY\n");
#endif
		if (!standingby) {
			sig_video_no_sync(cpssp->port_vga->video, cpssp);
			standingby = 1;
		}
		return;
	} else {
		standingby = 0;
	}

	pixel_format = _cirrus_get_pixel_format(cpssp);
	start_offset = _cirrus_get_display_start_offset(cpssp);
	pitch = _cirrus_get_display_pitch(cpssp);

	switch (pixel_format) {
	case VGA_COMPATIBILITY:
		_cirrus_gen_vga_compatibility(cpssp, video, width, height,
						start_offset, pitch);
		break;
	case EIGHT_BPP_GRAYSCALE:
		_cirrus_gen_8bpp_grayscale(cpssp, video, width, height,
						start_offset, pitch);
		break;
	case EIGHT_BPP_DIRECT_COLOR:
		_cirrus_gen_8bpp_direct_color(cpssp, video, width, height,
						start_offset, pitch);
		break;
	case FIFTEEN_BPP_MODE:
		_cirrus_gen_555_mode(cpssp, video, width, height,
					start_offset, pitch);
		break;
	case FIFTEEN_BPP_MIX_MODE:
		_cirrus_gen_555_mix_mode(cpssp, video, width, height,
					start_offset, pitch);
		break;
	case XGA:
		_cirrus_gen_xga(cpssp, video, width, height,
					start_offset, pitch);
		break;
	case TWENTYFOUR_BPP_MODE:
		_cirrus_gen_888_mode(cpssp, video, width, height,
					start_offset, pitch);
		break;
	case THIRTYTWO_BPP_ALPHA_MODE:
		_cirrus_gen_8888_alpha_mode(cpssp, video, width, height,
					start_offset, pitch);
		break;
	default:
		faum_log(FAUM_LOG_WARNING, __FUNCTION__, "",
			 "Unknown pixel format, cannot do video.\n");
		break;
	}
}
