im_hangul_ic_focus_in (GtkIMContext *context)
{
  int input_mode;
  GtkIMContextHangul *hcontext;

  g_return_if_fail (context != NULL);

  hcontext = GTK_IM_CONTEXT_HANGUL(context);
  input_mode = im_hangul_ic_get_toplevel_input_mode(hcontext);
  im_hangul_set_input_mode(hcontext, input_mode);

  current_focused_ic = context;
}
