keyPressEvent(XKeyEvent &event) {
    KeySym ks;
    char keychar[1];
    XLookupString(&event, keychar, 1, &ks, 0);

    if (IsModifierKey(ks))
        return;

    switch (ks) {
    case XK_Up:
        prevItem();
        break;
    case XK_Down:
        nextItem();
        break;
    case XK_Left:
        enterParent();
        break;
    case XK_Right:
        enterSubmenu();
        break;
    case XK_Escape:
        hide();
        break;
    case XK_Return:

        if (validIndex(m_which_press) &&
            isItemEnabled(m_which_press)) {
            menuitems[m_which_press]->click(1, event.time);
            itemSelected(1, m_which_press);
            m_need_update = true;
            updateMenu();
        }
        break;
    default:
        break;
    }
}
