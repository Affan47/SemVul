inputline_handler(GtkWidget *w, GdkEventKey *ev)
{
  if ((ev->state & GDK_CONTROL_MASK)) {

    switch (ev->keyval) {
    case GDK_b:
      inputline_make_tag(GTK_ENTRY(w), TTT_BOLD);
      return TRUE;

    case GDK_c:
      inputline_make_tag(GTK_ENTRY(w), TTT_COLOR);
      return TRUE;

    case GDK_i:
      inputline_make_tag(GTK_ENTRY(w), TTT_ITALIC);
      return TRUE;

    case GDK_s:
      inputline_make_tag(GTK_ENTRY(w), TTT_STRIKE);
      return TRUE;

    case GDK_u:
      inputline_make_tag(GTK_ENTRY(w), TTT_UNDERLINE);
      return TRUE;

    default:
      break;
    }

  } else {

    switch (ev->keyval) {
    case GDK_Up:
      if (history_pos < genlist_size(history_list) - 1) {
        gtk_entry_set_text(GTK_ENTRY(w),
                           genlist_get(history_list, ++history_pos));
        gtk_editable_set_position(GTK_EDITABLE(w), -1);
      }
      return TRUE;

    case GDK_Down:
      if (history_pos >= 0) {
        history_pos--;
      }

      if (history_pos >= 0) {
        gtk_entry_set_text(GTK_ENTRY(w),
                           genlist_get(history_list, history_pos));
      } else {
        gtk_entry_set_text(GTK_ENTRY(w), "");
      }
      gtk_editable_set_position(GTK_EDITABLE(w), -1);
      return TRUE;

    case GDK_Tab:
      if (gui_gtk2_chatline_autocompletion) {
        return chatline_autocomplete(GTK_EDITABLE(w));
      }

    default:
      break;
    }
  }

  return FALSE;
}
