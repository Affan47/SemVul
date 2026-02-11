xim_get_area(XRectangle * preedit_rect, XRectangle * status_rect, XRectangle * needed_rect)
{
    preedit_rect->x = needed_rect->width + (scrollbar_is_visible()
                                            && !(BITFIELD_IS_SET(eterm_options, ETERM_OPTIONS_SCROLLBAR_RIGHT))
                                            ? (scrollbar_trough_width()) : (0));
    preedit_rect->y = Height2Pixel(TERM_WINDOW_GET_ROWS() - 1);

    preedit_rect->width =
        Width2Pixel(TERM_WINDOW_GET_COLS() + 1) - needed_rect->width +
        (!(BITFIELD_IS_SET(eterm_options, ETERM_OPTIONS_SCROLLBAR_RIGHT)) ? (scrollbar_trough_width()) : 0);
    preedit_rect->height = Height2Pixel(1);

    status_rect->x = (scrollbar_is_visible()
                      && !(BITFIELD_IS_SET(eterm_options, ETERM_OPTIONS_SCROLLBAR_RIGHT))) ? (scrollbar_trough_width()) : 0;
    status_rect->y = Height2Pixel(TERM_WINDOW_GET_ROWS() - 1);

    status_rect->width = needed_rect->width ? needed_rect->width : Width2Pixel(TERM_WINDOW_GET_COLS() + 1);
    status_rect->height = Height2Pixel(1);
}
