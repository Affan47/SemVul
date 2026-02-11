getAttributeNS( const DOMString &namespaceURI,
                                   const DOMString &localName)
{
    if (!impl) throw DOMException(DOMException::NOT_FOUND_ERR);
    ElementImpl* e = static_cast<ElementImpl*>(impl);
    int exceptioncode = 0;
    DOMString ret = e->getAttributeNS(namespaceURI, localName, exceptioncode);
    if (exceptioncode)
        throw DOMException(exceptioncode);
    return ret;
}
