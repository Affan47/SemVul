get_object_types (void)
{
    gpointer g_object_class;
    gint i = 0;
    object_types[i++] = fm_bookmarks_get_type ();
    object_types[i++] = fm_cell_renderer_pixbuf_get_type ();
    object_types[i++] = fm_cell_renderer_text_get_type ();
    object_types[i++] = fm_config_get_type ();
    object_types[i++] = fm_deep_count_job_get_type ();
    object_types[i++] = fm_dir_list_job_get_type ();
    object_types[i++] = fm_dir_tree_model_get_type ();
    object_types[i++] = fm_dir_tree_view_get_type ();
    object_types[i++] = fm_dnd_dest_get_type ();
    object_types[i++] = fm_dnd_src_get_type ();
    object_types[i++] = fm_dummy_monitor_get_type ();
    object_types[i++] = fm_file_get_type ();
    object_types[i++] = fm_file_info_job_get_type ();
    object_types[i++] = fm_file_ops_job_get_type ();
    object_types[i++] = fm_folder_get_type ();
    object_types[i++] = fm_folder_model_get_type ();
    object_types[i++] = fm_folder_view_get_type ();
    object_types[i++] = fm_job_get_type ();
    object_types[i++] = fm_menu_tool_item_get_type ();
    object_types[i++] = fm_nav_history_get_type ();
    object_types[i++] = fm_path_bar_get_type ();
    object_types[i++] = fm_path_entry_get_type ();
    object_types[i++] = fm_places_model_get_type ();
    object_types[i++] = fm_places_view_get_type ();
    object_types[i++] = fm_side_pane_get_type ();
    object_types[i++] = fm_simple_job_get_type ();
    object_types[i++] = fm_standard_view_get_type ();
    object_types[i++] = fm_tab_label_get_type ();
    object_types[i++] = fm_template_get_type ();
    object_types[i++] = fm_terminal_get_type ();
    object_types[i++] = fm_xml_file_get_type ();
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
