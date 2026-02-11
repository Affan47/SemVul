DocumentFragmentImpl(DocumentImplPtr owner) : NodeImpl()
{
    nodeType = DOCUMENT_FRAGMENT_NODE;
    nodeName = "#document-fragment";
    ownerDocument = owner;
}
