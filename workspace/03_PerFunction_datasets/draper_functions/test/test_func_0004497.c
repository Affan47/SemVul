createIndex(int i, int j){
    Index *index;

    index = (Index*)malloc(sizeof(Index));
    if(index == NULL)
        abort();

    index->i = i;
    index->j = j;
    index->nextIndex = NULL;
    return index;
}
