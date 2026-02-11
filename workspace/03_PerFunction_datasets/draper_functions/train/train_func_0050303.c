set_wordview_label (gint i)
{
	gtk_label_set_text (GTK_LABEL (wordview_label_1),
			    g_pReciteWord->now_zu_words.w[i]);
	gtk_label_set_text (GTK_LABEL (wordview_label_3),
			    g_pReciteWord->now_zu_words.m[i]);
	gchar aa[5];
	sprintf(aa,"%2d",i+1);
	gtk_label_set_text (GTK_LABEL (word_index_label),
			    aa);

	if (phonetic_ckbutton.status)
		gtk_widget_hide(phonetic_label.hbox);
	phonetic_label.set_text (g_pReciteWord->now_zu_words.t[i]);
	gint w;
	pango_layout_get_pixel_size(gtk_label_get_layout(GTK_LABEL(wordview_label_1)),&w,NULL);
	gtk_fixed_move (GTK_FIXED (g_pReciteWord->fixed),
			phonetic_label.hbox,
			Skin->skim.phonetic_label.x[0] +
			Skin->skim.wordview_label_1.x[0] +
			w


	,
			Skin->skim.phonetic_label.y[0]);
	if (phonetic_ckbutton.status)
		gtk_widget_show(phonetic_label.hbox);
	if (readword_ckbutton.status)
		readword(g_pReciteWord->now_zu_words.w[i]);
}
