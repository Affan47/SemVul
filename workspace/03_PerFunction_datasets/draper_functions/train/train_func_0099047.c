GQdestroywidget (Gwidget_t *widget) {
    switch (WQU->mode) {
    case G_QWSTRING:
        XtDestroyWidget (widget->w);
        break;
    case G_QWFILE:
        break;
    case G_QWCHOICE:
        XtDestroyWidget (widget->w);
        break;
    }
    return 0;
}
