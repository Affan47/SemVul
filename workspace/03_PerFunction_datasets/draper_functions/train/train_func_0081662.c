setPressedPixmap(Pixmap pm) {
    Pixmap my_pm = getPressedPixmap();

    if (my_pm != 0) {
        overrode_pressed = true;
        pm = my_pm;
    } else {
        overrode_pressed = false;
    }

    FbTk::Button::setPressedPixmap(pm);
}
