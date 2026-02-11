disp_tsin_select(int index)
{
  int x,y;

  if (index < 0)
    return;


  if (hime_edit_display_ap_only()) {
    getRootXY(current_CS->client_win, current_CS->spot_location.x, current_CS->spot_location.y, &x, &y);
  } else {
#if 1
    int i;

    for(i=index;i>=0; i--) {
      gtk_widget_show_now(chars[i].label);
      gtk_widget_show(chars[i].vbox);
      gtk_main_iteration_do(FALSE);

      int tx = get_widget_xy(gwin0, chars[i].vbox, &x, &y);

      if (tx>=0)
        break;
    }
#else
	get_widget_xy(gwin0, chars[index].vbox, &x, &y);
#endif
	get_win0_geom();
  }
  disp_selections(x, y);
}
