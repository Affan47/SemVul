compare_subtree(Module_table *mpt, List *list1, List *list2)
{
    List *li1;
    List *li2;

    for (li1 = list1, li2 = list2;
         li1 != NULL && li2 != NULL;
         li1 = li1->next, li2 = li2->next) {
        if (compare_sem_node(mpt, li1->data, li2->data) != 0)
            return FALSE;
    }

    if (li1 != NULL || li2 != NULL)
        return FALSE;

    return TRUE;
}
