get_object_types (void)
{
    gpointer g_object_class;
    gint i = 0;
    object_types[i++] = gimp_aspect_preview_get_type ();
    object_types[i++] = gimp_brush_select_button_get_type ();
    object_types[i++] = gimp_channel_combo_box_get_type ();
    object_types[i++] = gimp_drawable_combo_box_get_type ();
    object_types[i++] = gimp_drawable_preview_get_type ();
    object_types[i++] = gimp_font_select_button_get_type ();
    object_types[i++] = gimp_gradient_select_button_get_type ();
    object_types[i++] = gimp_image_combo_box_get_type ();
    object_types[i++] = gimp_layer_combo_box_get_type ();
    object_types[i++] = gimp_palette_select_button_get_type ();
    object_types[i++] = gimp_pattern_select_button_get_type ();
    object_types[i++] = gimp_proc_browser_dialog_get_type ();
    object_types[i++] = gimp_progress_bar_get_type ();
    object_types[i++] = gimp_select_button_get_type ();
    object_types[i++] = gimp_vectors_combo_box_get_type ();
    object_types[i++] = gimp_zoom_preview_get_type ();
    object_types[i] = 0;


    g_object_class = g_type_class_ref (G_TYPE_OBJECT);


    for (i=0; object_types[i]; i++)
      {
        if (G_TYPE_IS_CLASSED (object_types[i]))
          g_type_class_ref (object_types[i]);
        if (G_TYPE_IS_INTERFACE (object_types[i]))
          g_type_default_interface_ref (object_types[i]);
      }

    g_type_class_unref (g_object_class);

    return object_types;
}
