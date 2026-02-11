setStyle(unsigned long aStyle) {
    if (fStyle != aStyle) {
        fStyle = aStyle;

        if (flags & wfCreated) {
            if (fStyle & wsPointerMotion)
                fEventMask |= PointerMotionMask;


            if ((fStyle & wsDesktopAware) || (fStyle & wsManager) ||
                (fHandle != RootWindow(xapp->display(), DefaultScreen(xapp->display()))))
                fEventMask |=
                    StructureNotifyMask |
                    ColormapChangeMask |
                    PropertyChangeMask;

            if (fStyle & wsManager)
                fEventMask |=
                    FocusChangeMask |
                    SubstructureRedirectMask | SubstructureNotifyMask;

            fEventMask |= ButtonPressMask | ButtonReleaseMask | ButtonMotionMask;
            if (fHandle == RootWindow(xapp->display(), DefaultScreen(xapp->display())))
                if (!(fStyle & wsManager) || !grabRootWindow)
                    fEventMask &= ~(ButtonPressMask | ButtonReleaseMask | ButtonMotionMask);

            XSelectInput(xapp->display(), fHandle, fEventMask);
        }
    }
}
