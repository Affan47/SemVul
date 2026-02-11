List_addBack(List * list, void * data)
{
    ListNode * oldLastNode, *newNode;

    if(list == NULL || data == NULL)
        return false;

    newNode = createNode(data);
    if(newNode == NULL)
        return false;

    if(list->firstNode == NULL && list->lastNode == NULL)
    {
        return addFirstNode(list, newNode);
    }

    oldLastNode = list->lastNode;

    oldLastNode->nextNode = newNode;
    newNode->nextNode = NULL;

    list->lastNode = newNode;
    newNode->previousNode = oldLastNode;

    list->length++;

    return true;
}
