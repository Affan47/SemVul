FreeCache() {

    Display& d = *Session::instance()->default_display();
    XDisplay* dpy = d.rep()->display_;

    if (icache_) {
        delete icache_;
        icache_ = nil;
    }


    if (tx_pixmaps_) {
        Table2Iterator(OvPixmapTableBase) i(*tx_pixmaps_);

        for (; i.more(); i.next()) {
            XFreePixmap(dpy, i.cur_value());
        }
        delete tx_pixmaps_;
        tx_pixmaps_ = nil;
    }

    delete source_table_;
    source_table_ = nil;
}
