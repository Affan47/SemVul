getOffset() const {
    if(checkDir != 0 || start == segmentStart) {
        return (int32_t)(pos - rawStart);
    } else if(pos == start) {
        return (int32_t)(segmentStart - rawStart);
    } else {
        return (int32_t)(segmentLimit - rawStart);
    }
}
