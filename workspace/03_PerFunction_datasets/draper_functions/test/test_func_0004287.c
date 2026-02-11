chooseNameInGroup(Offset offset,
                                   UPropertyNameChoice choice) const {
    int32_t c = choice;
    if (!offset || c < 0) {
        return NULL;
    }
    const Offset* p = (const Offset*) getPointer(offset);
    while (c-- > 0) {
        if (*p++ < 0) return NULL;
    }
    Offset a = *p;
    if (a < 0) a = -a;
    return (const char*) getPointerNull(a);
}
