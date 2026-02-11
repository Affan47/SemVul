cleanUpData(void) {
    int32_t i, count;

    count=utm_countItems(normMem);
    for(i=0; i<count; ++i) {
        uset_close(norms[i].canonStart);
    }

    utm_close(normMem);
    utm_close(utf32Mem);
    utm_close(extraMem);
    utm_close(combiningTriplesMem);
    utrie_close(normTrie);
    utrie_close(norm32Trie);
    utrie_close(fcdTrie);
    utrie_close(auxTrie);

    uset_close(nfdQCNoSet);

    uprv_free(normTrie);
    uprv_free(norm32Trie);
    uprv_free(fcdTrie);
    uprv_free(auxTrie);
}
