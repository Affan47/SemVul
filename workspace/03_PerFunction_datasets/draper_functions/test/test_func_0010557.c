switchToWorkspace(long nw, bool takeCurrent) {
    if (nw >= 0 && nw < workspaceCount()) {
        YFrameWindow *frame = getFocus();
        if (takeCurrent && frame && !frame->isSticky()) {
            lockFocus();
            frame->wmOccupyAll();
            frame->wmRaise();
            activateWorkspace(nw);
            frame->wmOccupyOnlyWorkspace(nw);
            unlockFocus();
            frame->wmRaise();
            setFocus(frame);
        } else {
            activateWorkspace(nw);
        }
    }
}
