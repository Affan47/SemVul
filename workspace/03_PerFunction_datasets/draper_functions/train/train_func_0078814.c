visu_ui_panel_getView(VisuUiPanel *visu_ui_panel)
{
  g_return_val_if_fail(VISU_UI_IS_PANEL(visu_ui_panel), (VisuGlView*)0);

  return VISU_UI_PANEL_CLASS(G_OBJECT_GET_CLASS(visu_ui_panel))->viewObj;
}
