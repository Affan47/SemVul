set_frame_label(int i)
{
  GtkWidget *m=lookup_widget(sp->im_widget[i],"image_frame");
  gchar *t;
  double dist;
  g_assert(m);


  if(sp->im_editview[i] == EDITVIEW_EDIT
     || sp->im_editview[i] == EDITVIEW_EYES ) {
    if(i== MAIN_WIN)
	t=  _("template image");
    else
      t=  _("input image");
    if(sp-> im_filename_in[i])
      t=g_strdup_printf("%s: %s",t,FILENAME_UTF8(sp-> im_filename_in[i]));

  } else {
    if(i== MAIN_WIN)
      t= _("morphed image");
    else
      t= _("warped image");
    if(sp-> im_filename_out[i])
      t=g_strdup_printf("%s: %s",t,FILENAME_UTF8(sp-> im_filename_out[i]));
    }
  if ( i != MAIN_WIN ) {
    dist=meshDistance(&sp->im_mesh[i],&sp->im_mesh[MAIN_WIN],0);

    t=g_strdup_printf("%s, dist %.1f",t,dist);
  }
  gtk_frame_set_label(GTK_FRAME(m),t);
}
