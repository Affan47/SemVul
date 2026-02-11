foundNULTerminator() {
    if(state == CHECK_FWD && length < 0) {
        length = --pos;
        return TRUE;
    } else {
        return FALSE;
    }
}
