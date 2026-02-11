usrc_writeUTrie2Struct(FILE *f,
                       const char *prefix,
                       const UTrie2 *pTrie,
                       const char *indexName, const char *data32Name,
                       const char *postfix) {
    if(prefix!=NULL) {
        fputs(prefix, f);
    }
    if(pTrie->data32==NULL) {

        fprintf(
            f,
            "    %s,\n"
            "    %s+%ld,\n"
            "    NULL,\n",
            indexName,
            indexName,
            (long)pTrie->indexLength);
    } else {

        fprintf(
            f,
            "    %s,\n"
            "    NULL,\n"
            "    %s,\n",
            indexName,
            data32Name);
    }
    fprintf(
        f,
        "    %ld,\n"
        "    %ld,\n"
        "    0x%hx,\n"
        "    0x%hx,\n"
        "    0x%lx,\n"
        "    0x%lx,\n"
        "    0x%lx,\n"
        "    0x%lx,\n"
        "    NULL, 0, FALSE, FALSE, 0, NULL\n",
        (long)pTrie->indexLength, (long)pTrie->dataLength,
        (short)pTrie->index2NullOffset, (short)pTrie->dataNullOffset,
        (long)pTrie->initialValue, (long)pTrie->errorValue,
        (long)pTrie->highStart, (long)pTrie->highValueIndex);
    if(postfix!=NULL) {
        fputs(postfix, f);
    }
}
