previewgui_page_layout_radio_changed(GtkMenuItem *radioitem, gpointer data) {


    if (!gtk_check_menu_item_get_active (GTK_CHECK_MENU_ITEM(radioitem))) {
        return;
    }

    GuPreviewGui* pc = gui->previewgui;

    PopplerPageLayout pageLayout;
    if (gtk_check_menu_item_get_active(
                GTK_CHECK_MENU_ITEM(pc->page_layout_single_page))) {
        pageLayout = POPPLER_PAGE_LAYOUT_SINGLE_PAGE;
        config_set_value("pagelayout", "single_page");
    } else {
        pageLayout = POPPLER_PAGE_LAYOUT_ONE_COLUMN;
        config_set_value("pagelayout", "one_column");
    }

    previewgui_set_page_layout(gui->previewgui, pageLayout);
}
