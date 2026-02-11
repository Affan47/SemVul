readString(const unsigned char*& buffer, size_t& size) {
    size_t len = readU32(buffer, size);
    plString v = plString((pl_wchar_t*)buffer, (len-1) / sizeof(pl_wchar_t));
    buffer += len;
    size -= len;
    return v;
}
