previewgui_goto_page (GuPreviewGui* pc, int page) {

    page = MAX(page, 0);
    page = MIN(page, pc->n_pages-1);

    previewgui_set_current_page(pc, page);

    gint i;
    gdouble y = 0;

    if (!is_continuous(pc)) {
        update_scaled_size(pc);
        update_drawarea_size(pc);
    } else {
        for (i=0; i < page; i++) {
            y += get_page_height(pc, i)*pc->scale + get_page_margin(pc);
        }
    }


    previewgui_goto_xy(pc, gtk_adjustment_get_value(pc->hadj),
                           page_offset_y(pc, page, y));

    if (!is_continuous(pc)) {
        gtk_widget_queue_draw (pc->drawarea);
    }
}
