onZoomChanged(GtkSpinButton *spin, gpointer data _U_)
{
  int reDrawNeeded;

  if (!gtk_window_is_active(GTK_WINDOW(observeWindow)))
    return;

  reDrawNeeded =
    visu_gl_view_setGross(visu_ui_rendering_window_getGlView
                          (visu_ui_main_class_getDefaultRendering()),
                          (float)gtk_spin_button_get_value(spin));
  if (reDrawNeeded)
    VISU_REDRAW_ADD;
}
