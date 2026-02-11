TXT_HoveringOverWidget(TXT_UNCAST_ARG(widget))
{
    TXT_CAST_ARG(txt_widget_t, widget);
    txt_window_t *active_window;
    int x, y;


    active_window = TXT_GetActiveWindow();

    if (active_window == NULL || !TXT_ContainsWidget(active_window, widget))
    {
        return 0;
    }


    TXT_GetMousePosition(&x, &y);

    return (x >= widget->x && x < widget->x + widget->w
         && y >= widget->y && y < widget->y + widget->h);
}
