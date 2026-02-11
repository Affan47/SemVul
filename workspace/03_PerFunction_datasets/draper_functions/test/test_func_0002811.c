onRegionSelection(VisuInteractive *inter _U_, GList *nodes,
			      gpointer data)
{
  VisuData *dataObj;
  GtkTreeIter iter;
  VisuNodeArrayIter it;
  VisuGlExtMarks *marks;
  VisuGlView *view;

  dataObj = visu_ui_rendering_window_getData(VISU_UI_RENDERING_WINDOW(data));
  g_return_if_fail(dataObj);
  marks = visu_ui_rendering_window_getMarks(VISU_UI_RENDERING_WINDOW(data));
  view = visu_ui_rendering_window_getGlView(VISU_UI_RENDERING_WINDOW(data));


  visu_ui_value_io_setSensitiveSave(VISU_UI_VALUE_IO(valueIO), FALSE);

  visu_node_array_iterNew(VISU_NODE_ARRAY(dataObj), &it);
  for (visu_node_array_iterStartList(VISU_NODE_ARRAY(dataObj), &it, nodes), it.lst = (GList*)0;
       it.node; visu_node_array_iterNextList(VISU_NODE_ARRAY(dataObj), &it))
    {
      getIterPick(it.node->number, &iter);
      addNodeAtIter(dataObj, it.node, &iter,
                    visu_gl_ext_marks_getHighlightStatus(marks, it.node->number));
    }
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioDrawSelected)))
    {
      drawDataOnNode(dataObj, view, DRAW_SELECTED);
      VISU_REDRAW_ADD;
    }
  return;
}
