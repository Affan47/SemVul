audacious_remote_set_balance(DBusGProxy *proxy, gint b) {
    gint v = 0, vl = 0, vr = 0;

    if (b < -100)
        b = -100;
    if (b > 100)
        b = 100;

    v = audacious_remote_get_main_volume(proxy);

    if (b < 0) {
        vl = v;
        vr = (v * (100 - abs(b))) / 100;
    } else if (b > 0) {
        vl = (v * (100 - b)) / 100;
        vr = v;
    } else
        vl = vr = v;
    audacious_remote_set_volume(proxy, vl, vr);
}
