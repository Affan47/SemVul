getAvailableID(int32_t index) const {
    if (index < 0 || index >= availableIDs.size()) {
        index = 0;
    }
    return *(const UnicodeString*) availableIDs[index];
}
