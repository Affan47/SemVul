gap_cme_gui_upd_wgt_sensitivity (GapCmeGlobalParams *gpp)
{
  gboolean   sensitive;

  sensitive = FALSE;
  if(gpp->val.audioname1[0] != '\0')
  {
    if(g_file_test(gpp->val.audioname1, G_FILE_TEST_EXISTS))
    {
      sensitive = TRUE;
    }
  }

  gtk_widget_set_sensitive(gpp->cme__spinbutton_samplerate, sensitive);
  gtk_widget_set_sensitive(gpp->cme__button_gen_tmp_audfile, sensitive);

  sensitive = FALSE;
  if(gpp->val.ecp_sel.gui_proc[0] != '\0')
  {
      sensitive = TRUE;
  }

  gtk_widget_set_sensitive(gpp->cme__button_params, sensitive);

  sensitive = FALSE;
  if(gpp->val.storyboard_file[0] != '\0')
  {
    if(g_file_test(gpp->val.storyboard_file, G_FILE_TEST_EXISTS))
    {
      t_global_stb         *gstb;


      gstb = &global_stb;
      if((gstb->aud_total_sec > 0.0)
      && (gstb->vidhand_open_ok))
      {
        sensitive = TRUE;
      }
    }
  }
  gtk_widget_set_sensitive(gpp->cme__button_stb_audio, sensitive);

}
