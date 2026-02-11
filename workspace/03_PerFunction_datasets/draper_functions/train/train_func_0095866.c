operator==(const plUuid& other) const {
    if (fData1 != other.fData1 || fData2 != other.fData2 || fData3 != other.fData3)
        return false;
    return (memcmp(fData4, other.fData4, sizeof(fData4)) == 0);
}
