DoMaximize(long flags) {
    setState(WinStateRollup, 0);

    if (isMaximized()) {
#ifdef CONFIG_GUIEVENTS
        wmapp->signalGuiEvent(geWindowRestore);
#endif
        setState(WinStateMaximizedVert |
                 WinStateMaximizedHoriz |
                 WinStateMinimized, 0);
    } else {
#ifdef CONFIG_GUIEVENTS
        wmapp->signalGuiEvent(geWindowMax);
#endif
        setState(WinStateMaximizedVert |
                 WinStateMaximizedHoriz |
                 WinStateMinimized, flags);
    }
}
