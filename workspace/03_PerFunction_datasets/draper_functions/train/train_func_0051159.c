ensureCapacity(int32_t appendCapacity) {
    if(!ok) {
        return FALSE;
    }
    int32_t newCapacity = 2 * buffer.getCapacity();
    int32_t altCapacity = len + 2 * appendCapacity;
    if (newCapacity < altCapacity) {
        newCapacity = altCapacity;
    }
    if (newCapacity < 200) {
        newCapacity = 200;
    }
    if(buffer.resize(newCapacity, len)==NULL) {
        return ok = FALSE;
    }
    return TRUE;
}
