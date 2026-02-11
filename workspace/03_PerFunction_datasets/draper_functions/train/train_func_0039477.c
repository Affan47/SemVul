getElementsByTagName( const DOMString &tagName )
{
    if (!impl) return 0;
    return static_cast<ElementImpl*>(impl)->getElementsByTagName( tagName );
}
