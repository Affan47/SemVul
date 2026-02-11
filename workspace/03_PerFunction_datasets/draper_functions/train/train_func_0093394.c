raise() {
    if (this != manager->top(getActiveLayer())) {
        YWindow::raise();
        setAbove(manager->top(getActiveLayer()));
    }
}
