TXT_DrawWindowFrame(const char *title, int x, int y, int w, int h)
{
    txt_saved_colors_t colors;
    int x1, y1;
    int bx, by;

    TXT_SaveColors(&colors);
    TXT_FGColor(TXT_COLOR_BRIGHT_CYAN);

    for (y1=y; y1<y+h; ++y1)
    {


        by = y1 == y ? 0 :
             y1 == y + 2 && title != NULL ? 2 :
             y1 == y + h - 1 ? 3 : 1;

        for (x1=x; x1<x+w; ++x1)
        {
            bx = x1 == x ? 0 :
                 x1 == x + w - 1 ? 3 : 1;

            if (VALID_X(x1) && VALID_Y(y1))
            {
                TXT_GotoXY(x1, y1);
                TXT_PutChar(borders[by][bx]);
            }
        }
    }


    if (title != NULL)
    {
        TXT_GotoXY(x + 1, y + 1);
        TXT_BGColor(TXT_COLOR_GREY, 0);
        TXT_FGColor(TXT_COLOR_BLUE);

        for (x1=0; x1<w-2; ++x1)
        {
            TXT_DrawString(" ");
        }

        TXT_GotoXY(x + (w - strlen(title)) / 2, y + 1);
        TXT_DrawString(title);
    }


    TXT_DrawShadow(x + 2, y + h, w, 1);
    TXT_DrawShadow(x + w, y + 1, 2, h);

    TXT_RestoreColors(&colors);
}
