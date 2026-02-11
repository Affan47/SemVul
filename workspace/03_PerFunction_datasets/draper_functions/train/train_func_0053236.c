parent_resize(void)
{
    D_X11(("Called.\n"));
    update_size_hints();
    resize_parent(szHint.width, szHint.height);
    D_X11((" -> New parent width/height == %lux%lu\n", szHint.width, szHint.height));
    term_resize(szHint.width, szHint.height);
    scrollbar_resize(szHint.width, szHint.height - bbar_calc_docked_height(BBAR_DOCKED));
    bbar_resize_all(szHint.width);
}
