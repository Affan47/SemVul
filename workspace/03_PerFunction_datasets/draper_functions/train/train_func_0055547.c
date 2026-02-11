TXT_ScrollPaneDrawer(TXT_UNCAST_ARG(scrollpane))
{
    TXT_CAST_ARG(txt_scrollpane_t, scrollpane);
    int x1, y1, x2, y2;
    int scrollbars;


    x1 = scrollpane->widget.x,
    y1 = scrollpane->widget.y,
    x2 = x1 + scrollpane->w,
    y2 = y1 + scrollpane->h;

    scrollbars = NeedsScrollbars(scrollpane);

    if (scrollbars & SCROLLBAR_HORIZONTAL)
    {
        TXT_DrawHorizScrollbar(x1,
                               y1 + scrollpane->h,
                               scrollpane->w,
                               scrollpane->x,
                               FullWidth(scrollpane) - scrollpane->w);
    }

    if (scrollbars & SCROLLBAR_VERTICAL)
    {
        TXT_DrawVertScrollbar(x1 + scrollpane->w,
                              y1,
                              scrollpane->h,
                              scrollpane->y,
                              FullHeight(scrollpane) - scrollpane->h);
    }

    TXT_PushClipArea(x1, x2, y1, y2);


    if (scrollpane->child != NULL)
    {
        TXT_DrawWidget(scrollpane->child);
    }


    TXT_PopClipArea();
}
