set_status_combo_item (GphpeditStatusbar *statusbar,const gchar *label)
{
  GList *items = gphpedit_status_combo_box_get_items (GPHPEDIT_STATUS_COMBO_BOX(statusbar->priv->filetype_menu));
  GList *walk;
  for (walk = items; walk != NULL; walk = g_list_next (walk)) {
    const gchar *lbl = gphpedit_status_combo_box_get_item_text 	(GPHPEDIT_STATUS_COMBO_BOX(statusbar->priv->filetype_menu), (GtkMenuItem *)walk->data);
    if (g_strcmp0(label,lbl)==0) {
        gphpedit_status_combo_box_set_item (GPHPEDIT_STATUS_COMBO_BOX(statusbar->priv->filetype_menu),(GtkMenuItem *)walk->data);
        break;
    }
  }
  g_list_free (items);
}
