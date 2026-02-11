p_tabw_update_selection(GapStbTabWidgets  *tabw)
{
  GapStbFrameWidget *fw;
  GapStbMainGlobalParams  *sgpp;
  GdkColor      *bg_color;
  GdkColor      *fg_color;
  gint ii;

  if(tabw == NULL) { return; }

  sgpp = (GapStbMainGlobalParams  *)tabw->sgpp;
  if(sgpp == NULL) { return; }

  for(ii=0; ii < tabw->fw_tab_size; ii++)
  {
    fw = tabw->fw_tab[ii];

    bg_color = &sgpp->shell_window->style->bg[GTK_STATE_NORMAL];
    fg_color = &sgpp->shell_window->style->fg[GTK_STATE_NORMAL];
    if(fw->stb_elem_refptr)
    {
      if(fw->stb_elem_refptr->selected)
      {
         bg_color = &sgpp->shell_window->style->bg[GTK_STATE_SELECTED];
         fg_color = &sgpp->shell_window->style->fg[GTK_STATE_SELECTED];
      }
    }

    if(gap_debug) printf("p_tabw_update_selection: GTK_STYLE_SET_BACKGROUND bg_color: %d\n", (int)bg_color);


    gtk_widget_modify_bg(fw->event_box, GTK_STATE_NORMAL, bg_color);
    gtk_widget_modify_fg(fw->key_label, GTK_STATE_NORMAL, fg_color);
    gtk_widget_modify_fg(fw->val_label, GTK_STATE_NORMAL, fg_color);
  }

}
