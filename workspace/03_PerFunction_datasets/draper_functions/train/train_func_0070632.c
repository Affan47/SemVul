on_xtext_parameter_changed(const void *const event_infos) {
  GtkWidget *text_view = *((GtkWidget**)event_infos+1);
  GtkTextBuffer *const text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
  GtkTextIter it_start, it_end;
  gtk_text_buffer_get_bounds(text_buffer,&it_start,&it_end);
  const char *const s_value = gtk_text_buffer_get_text(text_buffer,&it_start,&it_end,false);
  char s_param[1024] = { 0 };
  if (s_value && *s_value) {
    CImg<char> _s_value = CImg<char>::string(s_value);
    cimg_for(_s_value,ptr,char) if (*ptr=='\"') *ptr = _dquote;
    cimg_snprintf(s_param,sizeof(s_param),"\"%s\"",_s_value.data());
  } else std::strcpy(s_param,"\"\"");
  set_filter_parameter(get_current_filter(),*(int*)event_infos,s_param);
  _create_dialog_gui = true;
}
