setTBody( HTMLTableSectionElementImpl *s )
{
    int exceptioncode = 0;
    NodeImpl* r;

    if(ElementImpl* firstBody = tFirstBody()) {
        replaceChild ( s, firstBody, exceptioncode );
        r = s;
    } else
        r = appendChild( s, exceptioncode );
    firstBody = s;

    return r;
}
