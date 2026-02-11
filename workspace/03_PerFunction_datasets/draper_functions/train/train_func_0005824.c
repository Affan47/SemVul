indexOfElementWithNextUnit(int32_t i, int32_t unitIndex, UChar unit) const {
    while(unit==elements[i].charAt(unitIndex, strings)) {
        ++i;
    }
    return i;
}
