TXT_LabelDrawer(TXT_UNCAST_ARG(label))
{
    TXT_CAST_ARG(txt_label_t, label);
    unsigned int x, y;
    int origin_x, origin_y;
    unsigned int align_indent = 0;
    unsigned int w;

    w = label->widget.w;

    if (label->bgcolor >= 0)
    {
        TXT_BGColor(label->bgcolor, 0);
    }
    if (label->fgcolor >= 0)
    {
        TXT_FGColor(label->fgcolor);
    }

    TXT_GetXY(&origin_x, &origin_y);

    for (y=0; y<label->h; ++y)
    {


        switch (label->widget.align)
        {
            case TXT_HORIZ_LEFT:
                align_indent = 0;
                break;
            case TXT_HORIZ_CENTER:
                align_indent = (label->w - strlen(label->lines[y])) / 2;
                break;
            case TXT_HORIZ_RIGHT:
                align_indent = label->w - strlen(label->lines[y]);
                break;
        }


        TXT_GotoXY(origin_x, origin_y + y);


        for (x=0; x<align_indent; ++x)
        {
            TXT_DrawString(" ");
        }


        TXT_DrawUTF8String(label->lines[y]);
        x += TXT_UTF8_Strlen(label->lines[y]);


        for (; x<w; ++x)
        {
            TXT_DrawString(" ");
        }
    }
}
