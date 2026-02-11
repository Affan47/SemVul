geom_changed(gconf_block *b)
{
    int i, j;

    ENTER;
    i = gtk_combo_box_get_active(GTK_COMBO_BOX(allign_opt));
    gtk_widget_set_sensitive(margin_spin, (i != ALLIGN_CENTER));
    i = gtk_combo_box_get_active(GTK_COMBO_BOX(width_opt));
    gtk_widget_set_sensitive(width_spin, (i != WIDTH_REQUEST));
    if (i == WIDTH_PERCENT)
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(width_spin), 0, 100);
    else if (i == WIDTH_PIXEL) {
        XCG(b->data, "edge", &j, enum, edge_enum);
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(width_spin), 0,
            (j == EDGE_RIGHT || j == EDGE_LEFT)
            ? gdk_screen_height() : gdk_screen_width());
    }
    RET();
}
