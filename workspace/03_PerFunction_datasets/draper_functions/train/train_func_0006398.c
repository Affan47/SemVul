editbar_add_tool_button(struct editbar *eb,
                                    enum editor_tool_type ett)
{
  GdkPixbuf *pixbuf;
  GtkWidget *image, *button, *hbox;
  GtkRadioButton *parent = NULL;
  struct sprite *sprite;
  int i;

  if (!eb || !(0 <= ett && ett < NUM_EDITOR_TOOL_TYPES)) {
    return;
  }

  for (i = 0; i < NUM_EDITOR_TOOL_TYPES; i++) {
    if (eb->tool_buttons[i] != NULL) {
      parent = GTK_RADIO_BUTTON(eb->tool_buttons[i]);
      break;
    }
  }

  if (parent == NULL) {
    button = gtk_radio_button_new(NULL);
  } else {
    button = gtk_radio_button_new_from_widget(parent);
  }

  sprite = editor_tool_get_sprite(ett);
  fc_assert_ret(sprite != NULL);
  pixbuf = sprite_get_pixbuf(sprite);
  image = gtk_image_new_from_pixbuf(pixbuf);
  g_object_unref(G_OBJECT(pixbuf));

  gtk_container_add(GTK_CONTAINER(button), image);
  gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(button), FALSE);
  gtk_widget_set_tooltip_text(button, editor_tool_get_tooltip(ett));
  gtk_size_group_add_widget(eb->size_group, button);
  gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);
  gtk_button_set_focus_on_click(GTK_BUTTON(button), FALSE);

  g_signal_connect(button, "toggled",
      G_CALLBACK(editbar_tool_button_toggled), GINT_TO_POINTER(ett));
  g_signal_connect(button, "button_press_event",
      G_CALLBACK(editbar_tool_button_mouse_click), GINT_TO_POINTER(ett));

  hbox = eb->widget;
  gtk_container_add(GTK_CONTAINER(hbox), button);
  eb->tool_buttons[ett] = button;

  if (editor_tool_has_value(ett)) {
    eb->tool_selectors[ett] = create_tool_value_selector(eb, ett);
  }
}
