hide_win0()
{
  if (!gwin0)
    return;

  gtk_widget_hide(gwin0);
  if (destroy_window)
    destroy_win0();
  else
    destroy_top_bin();

  hide_selections_win();
  hide_win_sym();
}
