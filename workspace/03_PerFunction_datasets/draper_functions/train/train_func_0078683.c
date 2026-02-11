Index (ClassInfo* info) {
    for (int i = 0; i < _count; ++i) {
        if (info == _buf[i]) {
            return i;
        }
    }
    return -1;
}
