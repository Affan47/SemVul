mapClient(Window win) {
    YFrameWindow *frame = findFrame(win);

    MSG(("mapping window 0x%lX", win));
    if (frame == 0)
        return manageClient(win, true);
    else {
        frame->setState(WinStateMinimized | WinStateHidden, 0);
        if (clickFocus || !strongPointerFocus)
            frame->activate(true);
    }

    return frame;
}
