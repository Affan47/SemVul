handleClick(const XButtonEvent &up, int count) {
    if (count >= 2 && (count % 2 == 0)) {
        if (up.button == (unsigned) titleMaximizeButton &&
            ISMASK(KEY_MODMASK(up.state), 0, ControlMask))
        {
            if (getFrame()->canMaximize())
                getFrame()->wmMaximize();
        } else if (up.button == (unsigned) titleMaximizeButton &&
                   ISMASK(KEY_MODMASK(up.state), ShiftMask, ControlMask))
        {
            if (getFrame()->canMaximize())
                getFrame()->wmMaximizeVert();
        } else if (up.button == (unsigned) titleMaximizeButton && xapp->AltMask &&
                   ISMASK(KEY_MODMASK(up.state), xapp->AltMask + ShiftMask, ControlMask))
        {
            if (getFrame()->canMaximize())
                getFrame()->wmMaximizeHorz();
        } else if (up.button == (unsigned) titleRollupButton &&
                 ISMASK(KEY_MODMASK(up.state), 0, ControlMask))
        {
            if (getFrame()->canRollup())
                getFrame()->wmRollup();
        } else if (up.button == (unsigned) titleRollupButton &&
                   ISMASK(KEY_MODMASK(up.state), ShiftMask, ControlMask))
        {
            if (getFrame()->canMaximize())
                getFrame()->wmMaximizeHorz();
        }
    } else if (count == 1) {
        if (up.button == 3 && (KEY_MODMASK(up.state) & (xapp->AltMask)) == 0) {
            getFrame()->popupSystemMenu(this, up.x_root, up.y_root,
                                        YPopupWindow::pfCanFlipVertical |
                                        YPopupWindow::pfCanFlipHorizontal);
        } else if (up.button == 1) {
            if (KEY_MODMASK(up.state) == xapp->AltMask) {
                if (getFrame()->canLower()) getFrame()->wmLower();
            } else if (lowerOnClickWhenRaised &&
                       (buttonRaiseMask & (1 << (up.button - 1))) &&
                       ((up.state & (ControlMask | xapp->ButtonMask)) ==
                        Button1Mask))
            {
                if (!wasCanRaise) {
                    if (getFrame()->canLower())
                        getFrame()->wmLower();
                    wasCanRaise = true;
                }
            }
        }
    }
}
