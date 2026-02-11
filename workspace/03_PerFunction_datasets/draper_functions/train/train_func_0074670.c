dll_iteratorDeleteCurrentNode(list_t list, IteratorID iterID,
        void (*free_data)(void*))
{

    if (list == NULL) {
        fprintf(stderr, "dll_iteratorDeleteCurrentNode - Error: DLList has not been initialized\n");
        return -1;
    }
    if(dll_isempty(list)) {
        fprintf(stderr, "dll_iteratorDeleteCurrentNode - Error: DLList is empty\n"
                "\tDeleting all iterators now...\n");

        dll_iteratorDeleteAll(list);
        return 1;
    }

    int idx = dll_iteratorGetIdxWithID(list, iterID);
    if (idx == -1) {
        fprintf(stderr, "dll_iteratorDeleteCurrentNode - Error: "
                "Iterator with ID == %d wasn't found\n", iterID);
        return -1;
    }

    dllnodeptr current = (list->iteratorsArray[idx]).node;

    int setIteratorToEnd = 0;
    if (dll_iteratorNext(list, iterID) == 2) {


        setIteratorToEnd = 1;
    }

    if (current == list->head) {
            if (current != list->tail) {

                (current->next)->previous = NULL;
                list->head = current->next;
                list->size--;
                (*free_data)((void*) current->data);
                free(current);
                current = NULL;
            }
            else {

                list->head = NULL;
                list->tail = NULL;
                list->size--;
                (*free_data)((void*) current->data);
                free(current);
                current = NULL;


                dll_iteratorDeleteAll(list);
                return 1;
            }
        }
        else if (current == list->tail) {
            list->tail = current->previous;

            (current->previous)->next = NULL;
            list->size--;
            (*free_data)((void*)current->data);
            free(current);
            current = NULL;
            if (setIteratorToEnd) {
                if (dll_iteratorEnd(list, iterID) < 0) {
                    fprintf(stderr, "dll_iteratorDeleteCurrentNode - Error:"
                            "Could not set iterator to the end of the list\n");
                    return -1;
                }
            }
        }
        else {
            (current->previous)->next = current->next;
            (current->next)->previous = current->previous;
            list->size--;
            (*free_data)((void*)current->data);
            free(current);
            current = NULL;
        }
    return 0;
}
