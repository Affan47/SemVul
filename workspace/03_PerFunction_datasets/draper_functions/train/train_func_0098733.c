importNode( const Node & importedNode, bool deep )
{
    if (!impl)
	throw DOMException(DOMException::INVALID_STATE_ERR);

    int exceptioncode = 0;
    NodeImpl *r = static_cast<DocumentImpl*>(impl)->importNode(importedNode.handle(), deep, exceptioncode);
    if (exceptioncode)
	throw DOMException(exceptioncode);
    return r;
}
