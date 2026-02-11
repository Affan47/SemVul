handleDestroyWindow(const XDestroyWindowEvent &destroyWindow) {
    if (destroyWindow.window == fHandle) {
        flags |= wfDestroyed;
        removeAllIgnoreUnmap(destroyWindow.window);
    }
}
