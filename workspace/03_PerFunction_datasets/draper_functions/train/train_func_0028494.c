dll_iteratorUpdate(list_t list, dllnodeptr old, dllnodeptr new)
 {
    if (dll_isempty(list))
        dll_iteratorDeleteAll(list);
    else {
        int idx;
        for (idx = 0; idx < list->iteratorsCount; idx++) {
            if ((list->iteratorsArray[idx]).node == old)
                (list->iteratorsArray[idx]).node = new;
        }
    }
 }
