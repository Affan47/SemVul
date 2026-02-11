SList_pop(SList *slist){
    register gpointer data;
    register SListNode *sln;
    g_assert(slist);
    data = slist->head->next->data;
    sln = slist->head;
    slist->head = sln->next;
    SListNode_free(slist->set, sln);
    return data;
    }
