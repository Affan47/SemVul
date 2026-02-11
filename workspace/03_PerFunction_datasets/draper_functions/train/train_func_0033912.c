append( DcmObject *obj )
{
    if ( obj != NULL )
    {
        if ( DcmList::empty() )
            currentNode = firstNode = lastNode = new DcmListNode(obj);
        else
        {
            DcmListNode *node = new DcmListNode(obj);
            lastNode->nextNode = node;
            node->prevNode = lastNode;
            currentNode = lastNode = node;
        }
        cardinality++;
    }
    return obj;
}
