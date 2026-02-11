handleButton(const XButtonEvent &button) {
    if (rootProxy && button.window == handle() &&
        !(useRootButtons & (1 << (button.button - 1))) &&
       !((button.state & (ControlMask + xapp->AltMask)) == ControlMask + xapp->AltMask))
    {
        if (button.send_event == False) {
            XUngrabPointer(xapp->display(), CurrentTime);
            XSendEvent(xapp->display(),
                       rootProxy->handle(),
                       False,
                       SubstructureNotifyMask,
                       (XEvent *) &button);
        }
        return ;
    }
    YFrameWindow *frame = 0;
    if (useMouseWheel && ((frame = getFocus()) != 0) && button.type == ButtonPress &&
        ((KEY_MODMASK(button.state) == xapp->WinMask && xapp->WinMask) ||
         (KEY_MODMASK(button.state) == ControlMask + xapp->AltMask && xapp->AltMask)))
    {
        if (button.button == 4)
            frame->wmNextWindow();
        else if (button.button == 5)
            frame->wmPrevWindow();
    }
    if (button.type == ButtonPress) do {
#ifndef NO_CONFIGURE_MENUS
        if (button.button + 10 == (unsigned) rootMenuButton) {
            if (rootMenu)
                rootMenu->popup(0, 0, 0, button.x, button.y,
                                YPopupWindow::pfCanFlipVertical |
                                YPopupWindow::pfCanFlipHorizontal |
                                YPopupWindow::pfPopupMenu |
                                YPopupWindow::pfButtonDown);
            break;
        }
#endif
#ifdef CONFIG_WINMENU
        if (button.button + 10 == (unsigned) rootWinMenuButton) {
            popupWindowListMenu(this, button.x, button.y);
            break;
        }
#endif
    } while (0);
    YWindow::handleButton(button);
}
