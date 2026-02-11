cmd_delete (int interactive UNUSED, struct cmdarg **args UNUSED)
{
  XEvent ev;
  int status;

  if (current_window() == NULL)
    return cmdret_new (RET_FAILURE, NULL);

  ev.xclient.type = ClientMessage;
  ev.xclient.window = current_window()->w;
  ev.xclient.message_type = wm_protocols;
  ev.xclient.format = 32;
  ev.xclient.data.l[0] = wm_delete;
  ev.xclient.data.l[1] = CurrentTime;

  status = XSendEvent(dpy, current_window()->w, False, 0, &ev);
  if (status == 0)
    PRINT_DEBUG (("Delete window failed\n"));

  return cmdret_new (RET_SUCCESS, NULL);
}
