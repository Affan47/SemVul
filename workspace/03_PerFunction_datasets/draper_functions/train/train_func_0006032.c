update_load(void)
{
  double load;
  char tmp_buf[100];
  uint32_t xruns;

  if (jack_proxy_get_xruns(&xruns))
  {
    snprintf(tmp_buf, sizeof(tmp_buf),
             ngettext("%"PRIu32" dropout",
                      "%"PRIu32" dropouts",
                      xruns), xruns);

    set_xruns_text(tmp_buf);
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(g_xrun_progress_bar), tmp_buf);
  }
  else
  {
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(g_xrun_progress_bar), _("error"));
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(g_xrun_progress_bar), 0.0);
    set_xruns_text("?");
  }

  if (jack_proxy_get_dsp_load(&load))
  {
    if (load > g_jack_max_dsp_load)
    {
      g_jack_max_dsp_load = load;
      gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(g_xrun_progress_bar), load / 100.0);
    }

    snprintf(tmp_buf, sizeof(tmp_buf), _("DSP: %5.1f%% (%5.1f%%)"), (float)load, (float)g_jack_max_dsp_load);
    set_dsp_load_text(tmp_buf);
  }
  else
  {
    set_xruns_text("?");
  }

  if ((g_xruns == 0 && xruns != 0) || (g_xruns != 0 && xruns == 0))
  {
    g_xruns = xruns;
    studio_state_changed(NULL);
  }
  else
  {
    g_xruns = xruns;
  }
}
