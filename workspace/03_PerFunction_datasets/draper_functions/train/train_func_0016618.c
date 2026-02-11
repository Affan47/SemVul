onPairsCheckToggled(VisuUiMain *main, GtkToggleButton *toggle)
{
  gboolean res;
  VisuUiRenderingWindow *window;
  VisuData *dataObj;
  VisuGlView *view;

  res = gtk_toggle_button_get_active(toggle);
  visu_gl_ext_setActive(VISU_GL_EXT(visu_gl_ext_pairs_getDefault()), res);
  if (res)
    {
      window = VISU_UI_RENDERING_WINDOW(main->renderingWindow);
      dataObj = visu_ui_rendering_window_getData(window);
      view = visu_ui_rendering_window_getGlView(window);
      if (dataObj && view)
        {
          visu_gl_ext_pairs_draw(visu_gl_ext_pairs_getDefault());
          VISU_REDRAW_ADD;
        }
    }
  else
    VISU_REDRAW_ADD;
}
