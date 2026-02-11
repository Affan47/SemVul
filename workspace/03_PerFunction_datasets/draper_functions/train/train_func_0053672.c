coalesceDuplicates(UStack &nodes, UErrorCode &status) {

    if (U_FAILURE(status)) {
        return;
    }
    int32_t size = nodes.size();
    void **array = (void **)uprv_malloc(sizeof(void *)*size);
    if (array == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
        return;
    }
    (void) nodes.toArray(array);


    int32_t dupes = 0;
    long    passCount = 0;
#ifdef DEBUG_TRIE_DICT
    long    totalDupes = 0;
#endif
    do {
        BuildCompactTrieNode *node;
        BuildCompactTrieNode *first = NULL;
        BuildCompactTrieNode **p;
        BuildCompactTrieNode **pFirst = NULL;
        int32_t counter = size - 2;


        uprv_sortArray(array+2, counter, sizeof(void *), _sortBuildNodes, NULL, (passCount > 0), &status);
        dupes = 0;
        for (p = (BuildCompactTrieNode **)array + 2; counter > 0; --counter, ++p) {
            node = *p;
            if (node->fHasDuplicate) {
                if (first == NULL) {
                    first = node;
                    pFirst = p;
                }
                else if (_sortBuildNodes(NULL, pFirst, p) != 0) {

                    first = node;
                    pFirst = p;
                }
                else if (node->fNodeID != first->fNodeID) {

                    node->fNodeID = first->fNodeID;
                    dupes += 1;
                }
            }
            else {

                first = NULL;
                pFirst = NULL;
            }
        }
        passCount += 1;
#ifdef DEBUG_TRIE_DICT
        totalDupes += dupes;
        fprintf(stderr, "Trie node dupe removal, pass %d: %d nodes tagged\n", passCount, dupes);
#endif
    }
    while (dupes > 0);
#ifdef DEBUG_TRIE_DICT
    fprintf(stderr, "Trie node dupe removal complete: %d tagged in %d passes\n", totalDupes, passCount);
#endif


    uprv_free(array);
}
