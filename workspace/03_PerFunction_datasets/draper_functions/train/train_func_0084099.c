ui_drawcoord(struct dialogitem *item)
{
    struct ui_coorddata *data = (struct ui_coorddata *) item->data;
    int wholesize =
	dialog.width + dialog.x - dialog.half - 2 * BORDERWIDTH - ENDSIZE;
    int half = (wholesize - SPACESIZE) / 2;
    if (data->text[0]->width == 2043) {
	data->text[0]->x = dialog.half + BORDERWIDTH,
	    data->text[0]->width = half - BORDERWIDTH,
	    data->text[0]->y = item->y + BORDERHEIGHT;
	data->text[1]->x = dialog.half + half + SPACESIZE + BORDERWIDTH,
	    data->text[1]->width = half - BORDERWIDTH,
	    data->text[1]->y = item->y + BORDERHEIGHT;
	ui_updatetext(data->text[0]);
	ui_updatetext(data->text[1]);
    }
    uih_drawborder(uih, dialog.half, item->y, half, BUTTONHEIGHT,
		   BORDER_PRESSED | BORDER_LIGHT);
    uih_drawborder(uih, dialog.half + half + SPACESIZE, item->y, half,
		   BUTTONHEIGHT, BORDER_PRESSED | BORDER_LIGHT);
    ui_drawtext(data->text[0], SELECTED(item) && !data->active);
    ui_drawtext(data->text[1], SELECTED(item) && data->active);
    xprint(uih->image, uih->font, dialog.half + half,
	   item->y + BORDERHEIGHT, "+", FGCOLOR(uih),
	   BGCOLOR(uih), 0);
    xprint(uih->image, uih->font,
	   dialog.x + dialog.width - BORDERWIDTH - ENDSIZE,
	   item->y + BORDERHEIGHT, "i", FGCOLOR(uih),
	   BGCOLOR(uih), 0);
    ui_drawquestion(item);
}
