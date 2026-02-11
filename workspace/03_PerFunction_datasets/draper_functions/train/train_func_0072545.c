handleEvent(XEvent &event) {
    if (event.type == ConfigureNotify && event.xconfigure.window == window().window())
        configureNotifyEvent(event.xconfigure);
}
