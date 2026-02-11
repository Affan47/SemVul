change_widget (MxComboBox *box,
               GParamSpec *pspec,
               gpointer    userdata)
{
  GObjectClass *class;
  const gchar *typename;
  guint id;
  ClutterActor *actor, *vbox;
  GParamSpec **properties;
  guint n_properties;
  gint i;


  if (mx_bin_get_child (MX_BIN (data.frame)))
    clutter_actor_destroy (mx_bin_get_child (MX_BIN (data.frame)));

  typename = mx_combo_box_get_active_text (box);
  id = g_type_from_name (typename);

  actor = g_object_new (id, NULL);

  class = G_OBJECT_GET_CLASS (actor);

  mx_bin_set_child (MX_BIN (data.frame), actor);

  if (data.inspector)
    clutter_actor_destroy (data.inspector);

  vbox = mx_box_layout_new ();
  mx_box_layout_set_orientation (MX_BOX_LAYOUT (vbox),
                                 MX_ORIENTATION_VERTICAL);

  properties = g_object_class_list_properties (class, &n_properties);

  for (i = n_properties - 1; i >= 0; i--)
    {
      ClutterActor *editor;

      editor = create_property_editor (G_OBJECT (actor), properties[i]);


      if (g_str_equal (properties[i]->name, "label")
          || g_str_equal (properties[i]->name, "text"))
        g_object_set (actor, properties[i]->name, typename, NULL);

      if (editor)
        clutter_container_add_actor (CLUTTER_CONTAINER (vbox), editor);
    }


  if (g_str_equal (typename, "MxIcon"))
    g_object_set (actor, "icon-name", "face-smile", NULL);
  else if (g_str_equal (typename, "MxComboBox"))
    {
      mx_combo_box_set_active_text (MX_COMBO_BOX (actor), "MxComboBox");
      mx_combo_box_append_text (MX_COMBO_BOX (actor), "Item 1");
      mx_combo_box_append_text (MX_COMBO_BOX (actor), "Item 2");
      mx_combo_box_append_text (MX_COMBO_BOX (actor), "Item 3");
    }
  else if (g_str_equal (typename, "MxPathBar"))
    {
      mx_path_bar_push (MX_PATH_BAR (actor), "Mx");
      mx_path_bar_push (MX_PATH_BAR (actor), "Path");
      mx_path_bar_push (MX_PATH_BAR (actor), "Bar");
    }
  else if (g_str_equal (typename, "MxProgressBar"))
    {
      mx_progress_bar_set_progress (MX_PROGRESS_BAR (actor), 0.6);
    }
  else if (g_str_equal (typename, "MxScrollBar"))
    {
      mx_scroll_bar_set_adjustment (MX_SCROLL_BAR (actor),
                                    mx_adjustment_new_with_values (10, 0, 100,
                                                                   10, 25, 25));
    }

  data.inspector = mx_scroll_view_new ();
  clutter_actor_set_width (data.inspector, 300);
  clutter_container_add_actor (CLUTTER_CONTAINER (data.inspector), vbox);
  mx_table_add_actor_with_properties (MX_TABLE (data.table), data.inspector,
                                      0, 1,
                                      "x-expand", FALSE,
                                      NULL);
}
