revertFocus(BScreen &screen) {
    if (s_reverting || screen.isShuttingdown())
        return;

    Focusable *next_focus =
        screen.focusControl().lastFocusedWindow(screen.currentWorkspaceID());

    if (next_focus && next_focus->fbwindow() &&
        next_focus->fbwindow()->isStuck())
        FocusControl::s_reverting = true;


    if (!(next_focus && next_focus->focus())) {

        setFocusedWindow(0);

        if (FbTk::Menu::shownMenu())
            FbTk::Menu::shownMenu()->grabInputFocus();
        else {
            switch (screen.focusControl().focusModel()) {
            case FocusControl::MOUSEFOCUS:
            case FocusControl::STRICTMOUSEFOCUS:
                XSetInputFocus(screen.rootWindow().display(),
                               PointerRoot, None, CurrentTime);
                break;
            case FocusControl::CLICKFOCUS:
                screen.rootWindow().setInputFocus(RevertToPointerRoot,
                                                  CurrentTime);
                break;
            }
        }
    }

    FocusControl::s_reverting = false;
}
