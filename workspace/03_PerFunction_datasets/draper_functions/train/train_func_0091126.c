setElementAt(int32_t elem, int32_t index) {
    if (0 <= index && index < count) {
        elements[index] = elem;
    }

}
