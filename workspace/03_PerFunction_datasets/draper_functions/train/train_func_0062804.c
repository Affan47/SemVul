main_menu_item_select_cb (GtkMenuItem *item,
                          GtkAction *action)
{
        gchar *tooltip;

        g_object_get (G_OBJECT (action), "tooltip", &tooltip, NULL);
        if (tooltip != NULL)
                gva_main_statusbar_push (menu_tooltip_cid, "%s", tooltip);
        g_free (tooltip);
}
