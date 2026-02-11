onNewDir(GObject *obj _U_, VisuUiDirectoryType type, gpointer user _U_)
{
  DBG_fprintf(stderr, "Panel Browser: caught 'DirectoryChanged'"
	      " signal for type %d.\n", type);
  if (type == VISU_UI_DIR_FILE)
    visu_ui_panel_browser_setCurrentDirectory(visu_ui_getLastOpenDirectory());
}
