gnc_item_edit_update (GnomeCanvasItem *item, double *affine, ArtSVP *clip_path,
                      int flags)
{
    GncItemEdit *item_edit = GNC_ITEM_EDIT (item);
    gint toggle_x, toggle_y, toggle_width, toggle_height;
    gint x, y, w, h;

    if (GNOME_CANVAS_ITEM_CLASS (gnc_item_edit_parent_class)->update)
        (*GNOME_CANVAS_ITEM_CLASS(gnc_item_edit_parent_class)->update)
        (item, affine, clip_path, flags);

    gnc_item_edit_get_pixel_coords (item_edit, &x, &y, &w, &h);

    item->x1 = x;
    item->y1 = y;
    item->x2 = x + w;
    item->y2 = y + h;

    if (!item_edit->is_popup)
        return;

    toggle_height = h - (2 * (CELL_VPADDING + 1));
    toggle_width  = toggle_height;
    toggle_x      = x + w - (toggle_width + 3);
    toggle_y      = y + (h / 2) - (toggle_height / 2);

    item_edit->popup_toggle.toggle_offset = toggle_width + 3;

    gnc_item_edit_show_popup_toggle (item_edit, toggle_x, toggle_y,
                                     toggle_width, toggle_height,
                                     GTK_ANCHOR_NW);

    if (item_edit->show_popup)
        gnc_item_edit_show_popup (item_edit);
}
