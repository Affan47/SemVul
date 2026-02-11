setStartupId(const char* id) {
    if (p->role != Client) return;

    delete[] p->startup_id;
    p->startup_id = nstrdup(id);
    XChangeProperty(p->display, p->window, net_startup_id, UTF8_STRING, 8,
        PropModeReplace, reinterpret_cast< unsigned char* >( p->startup_id ),
        strlen( p->startup_id ));
}
