onStippleChanged(VisuUiStippleCombobox *combo _U_, guint value,
			     gpointer data _U_)
{
  int res;
  VisuUiPairsIter iter;
  gchar* label;

  DBG_fprintf(stderr, "Gtk Wire: caught 'stipple-selected' signal.\n");
  res = FALSE;

  for (visu_ui_pairs_iter_startSelected(&iter); iter.data;
       visu_ui_pairs_iter_nextSelected(&iter))
    {

      res = visu_gl_pairs_wire_setStipple(iter.data, (guint16)value) || res;
      label = visu_ui_pairs_wire_getValues(iter.data);

      visu_ui_pairs_setSpecificLabels(&(iter.iter), label);
      g_free(label);
    }

  if (res)
    {
      visu_gl_ext_pairs_draw(visu_gl_ext_pairs_getDefault());
      VISU_REDRAW_ADD;
    }
}
