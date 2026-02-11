TextImpl(DocumentImplPtr owner, const DOMString &value)
                               : CharacterDataImpl()
{
    nodeType      = TEXT_NODE;
    nodeName      = "#text";
    ownerDocument = owner;
    nodeValue     = value;
}
