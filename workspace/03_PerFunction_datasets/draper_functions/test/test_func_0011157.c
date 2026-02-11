doSkipWindow(const Focusable &win, const ClientPattern *pat) {
    const FluxboxWindow *fbwin = win.fbwindow();
    if (!fbwin || fbwin->isFocusHidden() || fbwin->isModal())
        return true;
    if (pat && !pat->match(win))
        return true;

    return false;
}
