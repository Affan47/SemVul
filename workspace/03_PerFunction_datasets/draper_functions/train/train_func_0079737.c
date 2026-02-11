refresh_gui_on_load(struct control * cp) {
	char str[1024];
	const char * chn = (cp->ir->nchan > 1) ? "channels" : "channel";
	float secs = (float)cp->ir->source_nfram / cp->ir->source_samplerate;
	char * filename_esc = g_markup_escape_text(cp->ir->source_path, -1);
	if (cp->ir->source_samplerate == (unsigned int)cp->ir->sample_rate) {
		snprintf(str, 1024,
			 XS1 "<b>%s</b>" XS2 "\n"
			 S1 "%d %s, %d samples, %d Hz, %.3f seconds" S2,
			 filename_esc,
			 cp->ir->nchan, chn, cp->ir->source_nfram,
			 cp->ir->source_samplerate, secs);
	} else {
		snprintf(str, 1024,
			 XS1 "<b>%s</b>" XS2 "\n"
			 S1 "%d %s, %d samples, %d Hz (resampled to %d Hz), %.3f seconds" S2,
			 filename_esc,
			 cp->ir->nchan, chn, cp->ir->source_nfram,
			 cp->ir->source_samplerate, (int)cp->ir->sample_rate, secs);
	}
	free(filename_esc);
	gtk_label_set_markup(GTK_LABEL(cp->wave_annot_label), str);

	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cp->chan_toggle[0]), FALSE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cp->chan_toggle[0]), TRUE);
	gtk_widget_set_sensitive(cp->chan_toggle[0], cp->ir->nchan > 1);
	for (int i = 1; i < 4; i++) {
		gtk_widget_set_sensitive(cp->chan_toggle[i], i < cp->ir->nchan);
	}

	set_agc_label(cp);
	ir_modeind_set_channels(IR_MODEIND(cp->mode_ind), cp->ir->nchan);
}
