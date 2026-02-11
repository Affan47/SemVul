disconnect_motion_signal (splotd *sp) {
  if (sp && sp->motion_id) {
    g_signal_handler_disconnect (G_OBJECT (sp->da), sp->motion_id);
    sp->motion_id = 0;
  }
}
