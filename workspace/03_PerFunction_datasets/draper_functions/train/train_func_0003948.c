nextNamedItem( const DOMString &name ) const
{
    QList<HTMLGenericFormElementImpl*>& l = static_cast<HTMLFormElementImpl*>( m_refNode )->formElements;


    for ( ; currentNamePos < (unsigned)l.count(); ++currentNamePos )
    {
        HTMLGenericFormElementImpl* el = l.at(currentNamePos);
        if (el->isEnumerable() &&
             ((el->getAttribute(ATTR_ID)   == name) ||
              (el->getAttribute(ATTR_NAME) == name)))
        {
            ++currentNamePos;
            foundInput = true;
            return el;
        }
    }


    if (foundInput) return 0;

    QList<HTMLImageElementImpl*>& il = static_cast<HTMLFormElementImpl*>( m_refNode )->imgElements;
    for ( ; currentNameImgPos < (unsigned)il.count(); ++currentNameImgPos )
    {
        HTMLImageElementImpl* el = il.at(currentNameImgPos);
        if ((el->getAttribute(ATTR_ID)   == name) ||
            (el->getAttribute(ATTR_NAME) == name))
        {
            ++currentNameImgPos;
            return el;
        }
    }

    return 0;
}
