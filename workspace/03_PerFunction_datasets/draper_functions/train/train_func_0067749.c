createCDATASection ( DOMStringImpl* data, int &exceptioncode )
{
    if (isHTMLDocument()) {
        exceptioncode = DOMException::NOT_SUPPORTED_ERR;
        return 0;
    }
    return new CDATASectionImpl( docPtr(), data );
}
