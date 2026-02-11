endElement( const QString& , const QString& , const QString&  )
{
    if (currentNode()->nodeType() == Node::TEXT_NODE)
        exitText();

    NodeImpl *node = popNode();
    if ( node ) {
        node->close();
        while ( currentNode()  && currentNode()->implicitNode() )
            popNode()->close();
    } else
        return false;


    if ((node->id() == ID_SCRIPT) || (node->id() == makeId(xhtmlNamespace, ID_SCRIPT)) || node->id() == WebCore::SVGNames::scriptTag.id())
        static_cast<XMLTokenizer*>(m_doc->tokenizer())->executeScript(node);

    return true;
}
