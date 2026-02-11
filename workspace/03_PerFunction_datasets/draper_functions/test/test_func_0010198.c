flush_text_node_edit(GF_Compositor *compositor, Bool final_flush)
{
	Bool signal;
	char *txt;
	u32 len;
	if (!compositor->edited_text) return;


	if (final_flush && compositor->sel_buffer_len) {
		memmove(&compositor->sel_buffer[compositor->caret_pos], &compositor->sel_buffer[compositor->caret_pos+1], sizeof(u16)*(compositor->sel_buffer_len-compositor->caret_pos));
		compositor->sel_buffer_len--;
		compositor->sel_buffer[compositor->sel_buffer_len] = 0;
	}


	if (*compositor->edited_text) {
		gf_free(*compositor->edited_text);
		*compositor->edited_text = NULL;
	}
	if (compositor->sel_buffer_len) {
		const u16 *lptr;
		txt = gf_malloc(sizeof(char)*2*compositor->sel_buffer_len);
		lptr = compositor->sel_buffer;
		len = gf_utf8_wcstombs(txt, 2*compositor->sel_buffer_len, &lptr);
		txt[len] = 0;
		*compositor->edited_text = gf_strdup(txt);
		gf_free(txt);
	}

	signal = final_flush;
	if ((compositor->focus_text_type==4) && (final_flush==1)) signal = 0;

	gf_node_dirty_set(compositor->focus_node, 0, 1);

	gf_sc_next_frame_state(compositor, GF_SC_DRAW_FRAME);


	gf_node_set_private(compositor->focus_highlight->node, NULL);


	if (final_flush) {
		GF_FieldInfo info;
		if (compositor->sel_buffer) gf_free(compositor->sel_buffer);
		compositor->sel_buffer = NULL;
		compositor->sel_buffer_len = compositor->sel_buffer_alloc = 0;
		compositor->edited_text = NULL;

		if (signal) {
			memset(&info, 0, sizeof(GF_FieldInfo));
			info.fieldIndex = (u32) -1;
			if (compositor->focus_text_type>=3) {
				gf_node_get_field(compositor->focus_node, 0, &info);
				gf_node_event_out(compositor->focus_node, 0);
			}
			gf_node_changed(compositor->focus_node, &info);
		}
	}
}
