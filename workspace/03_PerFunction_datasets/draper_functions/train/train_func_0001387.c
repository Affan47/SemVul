_cirrus_bitblt_system_to_screen(struct cpssp *cpssp)
{
#ifdef CIRRUS_DEBUG_BITBLT
	faum_log(FAUM_LOG_DEBUG, __FUNCTION__, "", "\n");
#endif


	if (cpssp->bitblt.mode & BITBLT_COLOR_EXPAND) {

		int bpl;

		bpl = cpssp->bitblt.width /
			cpssp->bitblt.color_expand_width;

		if (cpssp->bitblt.mode_extensions & BITBLT_32BIT_GRANULARITY) {


			bpl += ((cpssp->bitblt.dest_left_side_clipping
				 & BITBLT_SYSTEM_TO_SCREEN_DWORD_POINTER) >> 5)
				* 8;


			cpssp->bitblt.src_pitch = ((bpl + 31) >> 5) * 4;

		} else {

			cpssp->bitblt.src_pitch = (bpl + 7) >> 3;
		}
	} else {

		cpssp->bitblt.src_pitch =
			(cpssp->bitblt.width + 3) & ~3;
	}

	if (BITBLT_LINE_BUFFER_SIZE < cpssp->bitblt.src_pitch) {

#ifdef CIRRUS_DEBUG_BITBLT
		faum_log(FAUM_LOG_DEBUG, __FUNCTION__, "",
			 "System-to-screen line buffer too small, required "
			 "are %d bytes\n", cpssp->bitblt.src_pitch);
#endif
		_cirrus_bitblt_reset(cpssp);
		return;
	}


	cpssp->bitblt.src_counter =
		cpssp->bitblt.src_pitch * cpssp->bitblt.height;

	cpssp->bitblt.line_pointer = BITBLT_LINE_BUFFER_START;
	cpssp->bitblt.line_pointer_end =
		BITBLT_LINE_BUFFER_START + cpssp->bitblt.src_pitch;

	cpssp->bitblt.height = 1;
	cpssp->bitblt.source_pointer = BITBLT_LINE_BUFFER_START;
}
