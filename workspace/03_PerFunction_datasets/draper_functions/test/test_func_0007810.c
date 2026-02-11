handleClick(const XButtonEvent &up, int count) {
    if (up.button == 1) {
    } else if (up.button == 2) {
#ifdef CONFIG_WINLIST
        if (windowList)
            windowList->showFocused(up.x_root, up.y_root);
#endif
    } else {
        if (up.button == 3 && count == 1 && IS_BUTTON(up.state, Button3Mask)) {
            contextMenu(up.x_root, up.y_root);
        }
    }
}
