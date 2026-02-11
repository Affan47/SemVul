detachAtIndex(List * list, int index)
{
    ListNode * nodeToRemove, *previousNode, *nextNode;

    if(list == NULL)
        return NULL;

    if(index < 0 || index >= List_getLength(list))
        return NULL;

    if(index == 0)
        return detachFront(list);

    if(index == (List_getLength(list) - 1))
        return detachBack(list);

    nodeToRemove = nodeAtIndex(list, index);
    previousNode = nodeToRemove->previousNode;
    nextNode = nodeToRemove->nextNode;

    previousNode->nextNode = nextNode;
    nextNode->previousNode = previousNode;

    nodeToRemove->nextNode = NULL;
    nodeToRemove->previousNode = NULL;

    list->length--;

    return nodeToRemove;
}
