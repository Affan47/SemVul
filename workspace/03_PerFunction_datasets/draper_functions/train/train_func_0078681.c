startElement( const QString& namespaceURI, const QString& ,
                               const QString& qName, const QXmlAttributes& atts )
{
    if (currentNode()->nodeType() == Node::TEXT_NODE)
        exitText();

    DOMString nsURI;
    if (!namespaceURI.isNull())
        nsURI = DOMString(namespaceURI);
    else

        nsURI = DOMString("");
    ElementImpl *newElement = m_doc->createElementNS(nsURI,qName);
    if (!newElement)
        return false;
    int i;
    for (i = 0; i < atts.length(); i++) {
        int exceptioncode = 0;
        QString uriString = atts.uri(i);
        QString qnString  = atts.qName(i);
        fixUpNSURI(uriString, qnString);
        DOMString uri(uriString);
        DOMString qn(qnString);
        DOMString val(atts.value(i));
        newElement->setAttributeNS(uri, qn, val, exceptioncode);
        if (exceptioncode)
            return false;
    }

    if (newElement->id() == ID_SCRIPT || newElement->id() == makeId(xhtmlNamespace, ID_SCRIPT))
        static_cast<HTMLScriptElementImpl *>(newElement)->setCreatedByParser(true);


    bool attached = false;
    for ( NodeImpl *current = currentNode(); current; current = current->parent() ) {
        attached = current->addChild( newElement );
        if ( attached )
            break;
    }
    if (attached) {
        if (m_view && !newElement->attached() && !m_doc->hasPendingSheets())
            newElement->attach();
        pushNode( newElement );
        return true;
    }
    else {
        delete newElement;
        return false;
    }


}
