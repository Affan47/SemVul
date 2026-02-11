handleButton(const XButtonEvent &button) {
    if (button.type == ButtonPress) {
        if (!(button.state & ControlMask) &&
            (buttonRaiseMask & (1 << (button.button - 1))))
            getFrame()->wmRaise();
        manager->setFocus(getFrame(), false);
        if (button.button == 1) {
            selected = 2;
            repaint();
        }
    } else if (button.type == ButtonRelease) {
        if (button.button == 1) {
            if (selected == 2) {
                if (button.state & xapp->AltMask) {
                    getFrame()->wmLower();
                } else {
                    if (!(button.state & ControlMask))
                        getFrame()->wmRaise();
                    getFrame()->activate();
                }
            }
            selected = 0;
            repaint();
        }
    }
    YWindow::handleButton(button);
}
