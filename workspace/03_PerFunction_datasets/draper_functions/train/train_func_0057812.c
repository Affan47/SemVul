fixupNameToEnum(NameToEnum* n) {

    Offset* p = n->getNameArray();
    for (int32_t i=0; i<n->count; ++i) {
        p[i] = stringIndexToOffset(p[i]);
    }
}
