InterpretScrollKey(txt_scrollpane_t *scrollpane, int key)
{
    int maxy;

    switch (key)
    {
        case KEY_UPARROW:
            if (scrollpane->y > 0)
            {
                --scrollpane->y;
                return 1;
            }
            break;

        case KEY_DOWNARROW:
            if (scrollpane->y < FullHeight(scrollpane) - scrollpane->h)
            {
                ++scrollpane->y;
                return 1;
            }
            break;

        case KEY_LEFTARROW:
            if (scrollpane->x > 0)
            {
                --scrollpane->x;
                return 1;
            }
            break;

        case KEY_RIGHTARROW:
            if (scrollpane->x < FullWidth(scrollpane) - scrollpane->w)
            {
                ++scrollpane->x;
                return 1;
            }
            break;

        case KEY_PGUP:
            if (scrollpane->y > 0)
            {
                scrollpane->y -= scrollpane->h;
                if (scrollpane->y < 0)
                {
                    scrollpane->y = 0;
                }
                return 1;
            }
            break;

        case KEY_PGDN:
            maxy = FullHeight(scrollpane) - scrollpane->h;
            if (scrollpane->y < maxy)
            {
                scrollpane->y += scrollpane->h;
                if (scrollpane->y > maxy)
                {
                    scrollpane->y = maxy;
                }
                return 1;
            }
            break;

        default:
            break;
    }

    return 0;
}
