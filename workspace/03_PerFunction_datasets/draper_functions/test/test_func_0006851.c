default_page_sizes(void)
{
        if (!page_width)
        {
                char    *cp;

                cp = getenv("COLS");
                if (cp)
                {
                        int     n;

                        n = atoi(cp);
                        if (n > 0)
                        {
                                if (n < MIN_PAGE_WIDTH)
                                        n = MIN_PAGE_WIDTH;
                                if (n > MAX_PAGE_WIDTH)
                                        n = MAX_PAGE_WIDTH;
                                page_width = n;
                        }
                }
        }
        if (!page_length)
        {
                char    *cp;

                cp = getenv("LINES");
                if (cp)
                {
                        int     n;

                        n = atoi(cp);
                        if (n > 0)
                        {
                                if (n < MIN_PAGE_LENGTH)
                                        n = MIN_PAGE_LENGTH;
                                if (n > MAX_PAGE_LENGTH)
                                        n = MAX_PAGE_LENGTH;
                                page_length = n;
                        }
                }
        }

#ifdef TIOCGWINSZ
        if (!page_width || !page_length)
        {
                struct winsize  ws;

                if (ioctl(0, TIOCGWINSZ, &ws) == 0)
                {
                        if (!page_width && ws.ws_col > 0)
                        {
                                page_width = ws.ws_col;
                                if (page_width < MIN_PAGE_WIDTH)
                                        page_width = MIN_PAGE_WIDTH;
                                if (page_width > MAX_PAGE_WIDTH)
                                        page_width = MAX_PAGE_WIDTH;
                        }
                        if (!page_length && ws.ws_row > 0)
                        {
                                page_length = ws.ws_row;
                                if (page_length < MIN_PAGE_LENGTH)
                                        page_length = MIN_PAGE_LENGTH;
                                if (page_length > MAX_PAGE_LENGTH)
                                        page_length = MAX_PAGE_LENGTH;
                        }
                }
        }
#endif

        if (!page_width)
                page_width = DEFAULT_PAGE_WIDTH;
        if (!page_length)
                page_length = DEFAULT_PAGE_LENGTH;
}
