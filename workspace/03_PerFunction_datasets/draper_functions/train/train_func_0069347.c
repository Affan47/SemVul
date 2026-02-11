handleButton(const XButtonEvent &button) {
#ifdef CONFIG_WINLIST
    if ((button.type == ButtonRelease) &&
        (button.button == 1 || button.button == 3) &&
        (BUTTON_MODMASK(button.state) == Button1Mask + Button3Mask))
    {
        if (windowList)
            windowList->showFocused(button.x_root, button.y_root);
    } else
#endif
    {
        if (button.type == ButtonPress) {
            manager->updateWorkArea();
            if (button.button == 1) {
                if (button.state & xapp->AltMask)
                    lower();
                else if (!(button.state & ControlMask))
                    raise();
            }
        }
    }
    YWindow::handleButton(button);
}
