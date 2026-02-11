ui_keyok(struct dialogitem *item, int key)
{
    struct okdata *ok = (struct okdata *) item->data;
    switch (key) {
    case UIKEY_LEFT:
	if (ok->selected >= 1) {
	    ok->selected--;
	    uih->display = 1;
	    return 1;
	}
    case UIKEY_UP:
	PREV();
	return 1;
    case UIKEY_RIGHT:
    case UIKEY_TAB:
	if (ok->selected < 2) {
	    ok->selected++;
	    uih->display = 1;
	    return 1;
	}
    case UIKEY_DOWN:
	NEXT();
	return 1;
    case 13:
    case '\n':
	if (ok->selected <= 1)
	    ui_closedialog(!ok->selected);
	else
	    ui_help(dialog.item->shortname);
	return 1;
    }
    return 0;
}
