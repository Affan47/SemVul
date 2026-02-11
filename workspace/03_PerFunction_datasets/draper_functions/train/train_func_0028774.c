handleClick(const XButtonEvent &up, int count) {
    if (fAction == 0 && up.button == 1) {
        if ((count % 2) == 0) {
            setArmed(false, false);
            getFrame()->wmClose();
        }
    } else if (up.button == 3 && (KEY_MODMASK(up.state) & (xapp->AltMask)) == 0) {
        if (!isPopupActive())
            getFrame()->popupSystemMenu(this, up.x_root, up.y_root,
                                        YPopupWindow::pfCanFlipVertical |
                                        YPopupWindow::pfCanFlipHorizontal);
    }
}
