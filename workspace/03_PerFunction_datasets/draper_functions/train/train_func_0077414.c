efreet_menu_filter_matches(Efreet_Menu_Filter_Op *op, Efreet_Menu_Desktop *md)
{
    if (op->type == EFREET_MENU_FILTER_OP_OR)
        return efreet_menu_filter_or_matches(op, md);

    if (op->type == EFREET_MENU_FILTER_OP_AND)
        return efreet_menu_filter_and_matches(op, md);

    if (op->type == EFREET_MENU_FILTER_OP_NOT)
        return efreet_menu_filter_not_matches(op, md);

    return 0;
}
