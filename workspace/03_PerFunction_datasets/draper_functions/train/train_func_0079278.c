gotFocus() {
    if (parent() == 0 || isToplevel() || parent()->focused()) {
        if (!(flags & wfFocused)) {
            flags |= wfFocused;
            repaintFocus();
            if (fFocusedWindow)
                fFocusedWindow->gotFocus();
        }
    }
}
