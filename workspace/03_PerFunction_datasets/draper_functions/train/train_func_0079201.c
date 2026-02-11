cert_CombineNamesLists(CERTGeneralName *list1, CERTGeneralName *list2)
{
    PRCList *begin1;
    PRCList *begin2;
    PRCList *end1;
    PRCList *end2;

    if (list1 == NULL){
	return list2;
    } else if (list2 == NULL) {
	return list1;
    } else {
	begin1 = &list1->l;
	begin2 = &list2->l;
	end1 = list1->l.prev;
	end2 = list2->l.prev;
	end1->next = begin2;
	end2->next = begin1;
	begin1->prev = end2;
	begin2->prev = end1;
	return list1;
    }
}
