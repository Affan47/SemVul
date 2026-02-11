on_cme__entry_audio1_changed           (GtkEditable     *editable,
                                        GapCmeGlobalParams *gpp)
{
  GtkEntry *entry;

 if(gap_debug)
 {
   printf("CB: on_cme__entry_audio1_changed\n");
 }
 if(gpp == NULL) return;

 entry = GTK_ENTRY(gpp->cme__entry_audio1);
 if(entry)
 {
    g_snprintf(gpp->val.audioname1, sizeof(gpp->val.audioname1), "%s"
              , gtk_entry_get_text(entry));


    if(gpp->val.tmp_audfile[0] != '\0')
    {
      if(g_file_test(gpp->val.tmp_audfile, G_FILE_TEST_EXISTS))
      {
        g_remove(gpp->val.tmp_audfile);
      }
      gpp->val.tmp_audfile[0] = '\0';
    }
    gap_cme_gui_update_aud_labels (gpp);
    if(gpp->val.wav_samplerate1 > 0)
    {
      gpp->val.samplerate = gpp->val.wav_samplerate1;
      gtk_adjustment_set_value(GTK_ADJUSTMENT(gpp->cme__spinbutton_samplerate_adj)
                              , (gfloat)gpp->val.samplerate);
    }
 }


}
