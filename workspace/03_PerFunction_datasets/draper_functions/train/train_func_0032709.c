gotoChild()
{
#ifdef WITH_LIBXML
    if (Node != NULL)
    {
        Node = Node->xmlChildrenNode;

        while ((Node != NULL) && xmlIsBlankNode(Node))
            Node = Node->next;
    }
#endif
    return *this;
}
