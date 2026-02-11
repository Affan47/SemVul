makeAll32() {
    uint32_t *pNormData;
    uint32_t n;
    int32_t i, normLength, count;

    count=(int32_t)utm_countItems(normMem);
    for(i=0; i<count; ++i) {
        norms[i].value32=make32BitNorm(norms+i);
    }

    pNormData=utrie_getData(norm32Trie, &normLength);

    count=0;
    for(i=0; i<normLength; ++i) {
        n=pNormData[i];
        if(0!=(pNormData[i]=norms[n].value32)) {
            ++count;
        }
    }
}
