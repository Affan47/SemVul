fm_menu_tool_item_construct_contents (FmMenuToolItem *button)
{
    FmMenuToolItemPrivate *priv = button->priv;
    GtkOrientation orientation;

    orientation = gtk_tool_item_get_orientation (GTK_TOOL_ITEM (button));

    if (orientation == GTK_ORIENTATION_HORIZONTAL)
        gtk_arrow_set (GTK_ARROW (priv->arrow), GTK_ARROW_DOWN, GTK_SHADOW_NONE);
    else
        gtk_arrow_set (GTK_ARROW (priv->arrow), GTK_ARROW_RIGHT, GTK_SHADOW_NONE);

    gtk_button_set_relief (GTK_BUTTON (priv->arrow_button),
                           gtk_tool_item_get_relief_style (GTK_TOOL_ITEM (button)));

    gtk_widget_queue_resize (GTK_WIDGET (button));
}
