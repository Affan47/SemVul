update_controls(Documentable *document)
{
  gphpedit_debug(DEBUG_MAIN_WINDOW);
  if (!document) return ;
  gboolean read_only, can_modify, preview;
  g_object_get(document, "read_only", &read_only, "can_modify", &can_modify, "can_preview", &preview, NULL);
  menubar_update_controls(MENUBAR(main_window.menu), can_modify, preview, read_only);
  toolbar_update_controls(TOOLBAR(main_window.toolbar_main), can_modify, read_only);
}
