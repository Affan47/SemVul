menu_add_item(menu_t *menu, menuitem_t *item)
{
    ASSERT_RVAL(menu != NULL, 0);
    ASSERT_RVAL(item != NULL, 0);

    if (menu->numitems) {
        menu->numitems++;
        menu->items = (menuitem_t **) REALLOC(menu->items, sizeof(menuitem_t *) * menu->numitems);
    } else {
        menu->numitems = 1;
        menu->items = (menuitem_t **) MALLOC(sizeof(menuitem_t *));
    }

    menu->items[menu->numitems - 1] = item;
    return 1;

}
