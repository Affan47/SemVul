close ()
{
	gboolean tmp_b;
	rw_cfg_read_boolean(usercfgfile,
			     "firstrecite_skim", "readword",
			     &tmp_b);
	if (tmp_b!=readword_ckbutton.status)
	{
		rw_cfg_write_boolean(usercfgfile,
			     "firstrecite_skim", "readword",
			     readword_ckbutton.status);
	}
	rw_cfg_read_boolean(usercfgfile,
			     "firstrecite_skim", "showphonetic",
			     &tmp_b);
	if (tmp_b!=phonetic_ckbutton.status)
	{
		rw_cfg_write_boolean(usercfgfile,
			     "firstrecite_skim", "showphonetic",
			     phonetic_ckbutton.status);
	}
	rw_cfg_read_boolean(usercfgfile,
			     "firstrecite_skim", "showmeanlater",
			     &tmp_b);
	if (tmp_b!=showmeanlater_ckbutton.status)
	{
		rw_cfg_write_boolean(usercfgfile,
			     "firstrecite_skim", "showmeanlater",
			     showmeanlater_ckbutton.status);
	}
	rw_cfg_read_boolean(usercfgfile,
			     "firstrecite_skim", "upcase",
			     &tmp_b);
	if (tmp_b!=upcase_ckbutton.status)
	{
		rw_cfg_write_boolean(usercfgfile,
			     "firstrecite_skim", "upcase",
			     upcase_ckbutton.status);
	}

	if (timeout)
	{
		g_source_remove (timeout);
		timeout = 0;
	}

	if (dialog.fixed)
	{
		dialog.close();
	}
	start_button.destroy ();
	pause_button.destroy ();
	group_button.destroy ();
	test_button.destroy ();
	return_button.destroy ();
	readword_ckbutton.destroy ();
	phonetic_ckbutton.destroy ();
	showmeanlater_ckbutton.destroy ();
	upcase_ckbutton.destroy ();
	readword_button.destroy ();
	gtk_widget_destroy (wordlist_vscroll);
	gtk_widget_destroy (sentencelist_vscroll);
	gtk_widget_destroy (wordview_label_1);
	gtk_widget_destroy (wordview_label_3);
	gtk_widget_destroy (wordlist_scrollvalue_label);
	gtk_widget_destroy (word_index_label);
	gtk_widget_destroy (word_count_label);
	phonetic_label.destroy ();
	wordlist_item[0].destroy ();
	wordlist_item[1].destroy ();
	wordlist_item[2].destroy ();
	wordlist_item[3].destroy ();
	wordlist_item[4].destroy ();
	wordlist_item[5].destroy ();
}
