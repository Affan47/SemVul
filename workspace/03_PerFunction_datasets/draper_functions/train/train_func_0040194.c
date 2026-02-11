visu_ui_main_class_getDefaultRendering()
{
  g_return_val_if_fail(currentVisuUiMain, (VisuUiRenderingWindow*)0);

  DBG_fprintf(stderr, "Gtk Main: access the rendering window %p.\n",
	      (gpointer)currentVisuUiMain->renderingWindow);
  return VISU_UI_RENDERING_WINDOW(currentVisuUiMain->renderingWindow);
}
