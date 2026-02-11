getDataBlock(UNewTrie2 *trie, UChar32 c, UBool forLSCP) {
    int32_t i2, oldBlock, newBlock;

    i2=getIndex2Block(trie, c, forLSCP);
    if(i2<0) {
        return -1;
    }

    i2+=(c>>UTRIE2_SHIFT_2)&UTRIE2_INDEX_2_MASK;
    oldBlock=trie->index2[i2];
    if(isWritableBlock(trie, oldBlock)) {
        return oldBlock;
    }


    newBlock=allocDataBlock(trie, oldBlock);
    if(newBlock<0) {

        return -1;
    }
    setIndex2Entry(trie, i2, newBlock);
    return newBlock;
}
