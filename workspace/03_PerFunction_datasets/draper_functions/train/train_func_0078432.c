ui_drawok(struct dialogitem *item)
{
    struct okdata *ok = (struct okdata *) item->data;
    ui_drawbutton(gettext("OK"), ok->pressed == 0, SELECTED(item)
		  && ok->selected == 0, dialog.x + BORDERWIDTH + 1,
		  dialog.x + (dialog.width) / 3 - 1, item->y);
    ui_drawbutton(gettext("Cancel"), ok->pressed == 1, SELECTED(item)
		  && ok->selected == 1, dialog.x + (dialog.width) / 3 + 1,
		  dialog.x + 2 * dialog.width / 3 - BORDERWIDTH, item->y);
    ui_drawbutton(gettext("Help"), ok->pressed == 2, SELECTED(item)
		  && ok->selected == 2, dialog.x + 2 * (dialog.width) / 3,
		  dialog.x + dialog.width - BORDERWIDTH - 1, item->y);
}
