menulist_add_menu(menulist_t *list, menu_t *menu)
{
    ASSERT_RVAL(menu != NULL, list);

    if (list) {
        list->nummenus++;
        list->menus = (menu_t **) REALLOC(list->menus, sizeof(menu_t *) * list->nummenus);
    } else {
        list = (menulist_t *) MALLOC(sizeof(menulist_t));
        list->nummenus = 1;
        list->menus = (menu_t **) MALLOC(sizeof(menu_t *));
    }
    list->menus[list->nummenus - 1] = menu;
    return list;
}
