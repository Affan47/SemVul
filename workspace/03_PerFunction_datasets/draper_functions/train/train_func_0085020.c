page_offset_x(GuPreviewGui* pc, gint page, gdouble x) {
    if (page < 0 || page >= pc->n_pages) {
        return 0;
    }

    return x + (pc->width_scaled - get_page_width(pc, page)*pc->scale) / 2;
}
