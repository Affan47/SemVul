freeList(List *list){
    ListItem *item;
    item = list->firstItem;


    while(item != NULL){
        Index *index;
        index = item->index;
        while(index != NULL){
            Index *nextIndex;
            nextIndex = index->nextIndex;
            free(index);
            index = nextIndex;
        }
        ListItem *nextItem;
        nextItem = item->nextItem;
        free(item);
        item = nextItem;
    }
    free(list);
}
