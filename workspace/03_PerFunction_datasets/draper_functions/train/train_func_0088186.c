menu_item(const char *menu, int n)
{
    struct entry *item = firstitem;
    while (item != NULL) {
	if (!strcmp(menu, item->item->menuname)) {
	    if (!(item->item->flags & MENUFLAG_NOMENU))
		n--;
	    if (n < 0)
		return (item->item);
	}
	item = item->next;
    }
    return NULL;
}
