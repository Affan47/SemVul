PersistantSame(const char *form1, const char *form2) {
    const int *data1 = reinterpret_cast<const int *>(form1);
    const int *data2 = reinterpret_cast<const int *>(form2);
    if (data1[0] != data2[0])
        return false;
    int len = data1[0];
    for (int i=1;i<len*2+1;i++) {
        if (data1[i] != data2[i])
            return false;
    }
    return true;
}
