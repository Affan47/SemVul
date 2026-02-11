open_info_view() {
    if (!info_view || !info_view->window) {
        create_info_view();
    }
    else if (!gtk_widget_get_realized(info_view->window)) {
        gtkpod_display_widget(info_view->window);
    }

    gtk_widget_show_all(info_view->window);
}
