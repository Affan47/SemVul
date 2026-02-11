to32() const {
    if (v<0xffffffff && v!=0x7fffffff)
        return (uint32_t)v;
    if (v==ALL)
        return ALL32;
    return NONE32;
}
