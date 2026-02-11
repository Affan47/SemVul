wmHide() {
    if (isHidden()) {
#ifdef CONFIG_GUIEVENTS
        wmapp->signalGuiEvent(geWindowRestore);
#endif
        setState(WinStateHidden, 0);
    } else {
#ifdef CONFIG_GUIEVENTS
        wmapp->signalGuiEvent(geWindowHide);
#endif
        setState(WinStateHidden, WinStateHidden);
    }
    manager->focusLastWindow();
}
