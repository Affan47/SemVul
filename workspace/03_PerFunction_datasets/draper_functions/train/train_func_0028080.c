keysym() const {
    XEvent& xe = rep()->xevent_;
    if (xe.type == KeyPress) {
       int key_index = shift_is_down();
       return XLookupKeysym(&xe.xkey, key_index);
    }
    return XK_VoidSymbol;
}
