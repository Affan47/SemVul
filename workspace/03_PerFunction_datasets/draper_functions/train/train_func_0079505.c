ungrabKeys() {
    Display * display = App::instance()->display();
    for (int screen=0; screen<ScreenCount(display); screen++) {
        XUngrabKey(display, AnyKey, AnyModifier,
                   RootWindow(display, screen));
    }
}
