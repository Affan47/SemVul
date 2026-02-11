tool_color_addColor(ToolColor* color)
{
  int pos;

  g_return_val_if_fail(color, (ToolColor*)0);

  if (!tool_color_getByValues(&pos, color->rgba[0], color->rgba[1], color->rgba[2], color->rgba[3]))
    {
      color_storageArray = g_list_append(color_storageArray, (gpointer)color);
      DBG_fprintf(stderr, "Visu Tools : adding a new color at %p (%d).\n",
		  (gpointer)color_storageArray, g_list_length(color_storageArray));
      g_signal_emit_by_name(VISU_OBJECT_INSTANCE, "colorNewAvailable", (gpointer)color, NULL);
    }
  return color;
}
