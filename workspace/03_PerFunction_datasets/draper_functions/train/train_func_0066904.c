debug_check_frame_for_silence(struct ast_fax_session *s, unsigned int c2s, struct ast_frame *frame)
{
	struct debug_info_history *history = c2s ? &s->debug_info->c2s : &s->debug_info->s2c;
	int dspsilence;
	unsigned int last_consec_frames, last_consec_ms;
	unsigned char wassil;
	struct timeval diff;

	diff = ast_tvsub(ast_tvnow(), s->debug_info->base_tv);

	ast_dsp_reset(s->debug_info->dsp);
	ast_dsp_silence(s->debug_info->dsp, frame, &dspsilence);

	wassil = history->silence;
	history->silence = (dspsilence != 0) ? 1 : 0;
	if (history->silence != wassil) {
		last_consec_frames = history->consec_frames;
		last_consec_ms = history->consec_ms;
		history->consec_frames = 0;
		history->consec_ms = 0;

		if ((last_consec_frames != 0)) {
			ast_verb(6, "Channel '%s' fax session '%d', [ %.3ld.%.6ld ], %s sent %d frames (%d ms) of %s.\n",
				 s->channame, s->id, (long) diff.tv_sec, (long int) diff.tv_usec,
				 (c2s) ? "channel" : "stack", last_consec_frames, last_consec_ms,
				 (wassil) ? "silence" : "energy");
		}
	}

	history->consec_frames++;
	history->consec_ms += (frame->samples / 8);
}
