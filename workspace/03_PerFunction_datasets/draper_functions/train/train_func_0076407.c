TXT_DrawWindow(txt_window_t *window)
{
    txt_widget_t *widgets;

    TXT_LayoutWindow(window);

    if (window->table.widget.focused)
    {
        TXT_BGColor(TXT_ACTIVE_WINDOW_BACKGROUND, 0);
    }
    else
    {
        TXT_BGColor(TXT_INACTIVE_WINDOW_BACKGROUND, 0);
    }

    TXT_FGColor(TXT_COLOR_BRIGHT_WHITE);


    TXT_DrawWindowFrame(window->title,
                        window->window_x, window->window_y,
                        window->window_w, window->window_h);


    TXT_DrawWidget(window);


    widgets = (txt_widget_t *) window;

    if (widgets->y + widgets->h < window->window_y + window->window_h - 1)
    {


        TXT_DrawSeparator(window->window_x, widgets->y + widgets->h,
                          window->window_w);


        DrawActionArea(window);
    }
}
