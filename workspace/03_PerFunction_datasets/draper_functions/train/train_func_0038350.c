countElementUnits(int32_t start, int32_t limit, int32_t unitIndex) const {
    int32_t length=0;
    int32_t i=start;
    do {
        UChar unit=elements[i++].charAt(unitIndex, strings);
        while(i<limit && unit==elements[i].charAt(unitIndex, strings)) {
            ++i;
        }
        ++length;
    } while(i<limit);
    return length;
}
