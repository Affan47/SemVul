listNodesTrace(const AjPListNode node)
{
    ajDebug("listNodesTrace %p\n", node);

    while(node->Next)
    {
        ajDebug("node %p item %p -> %p\n", node, node->Item, node->Next);
        node = node->Next;
    }

    return;
}
