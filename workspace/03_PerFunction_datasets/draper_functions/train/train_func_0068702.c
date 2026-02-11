hide(bool interrupt_moving) {
   fbdbg<<"("<<__FUNCTION__<<")["<<this<<"]"<<endl;


    if (resizing)
        stopResizing(true);

    if (interrupt_moving) {
        if (moving)
            stopMoving(true);
        if (m_attaching_tab)
            attachTo(0, 0, true);
    }

    setState(IconicState, false);

    menu().hide();
    frame().hide();

    if (FocusControl::focusedFbWindow() == this)
        FocusControl::setFocusedWindow(0);
}
