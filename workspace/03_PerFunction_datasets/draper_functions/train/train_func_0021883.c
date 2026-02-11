getTextContent() throw(DOMException)
{
    DOMString buf;
    if (nodeType == TEXT_NODE          ||
	    nodeType == CDATA_SECTION_NODE ||
		nodeType == COMMENT_NODE       ||
		nodeType == PROCESSING_INSTRUCTION_NODE)
		buf = getNodeValue();
    else if (nodeType == ELEMENT_NODE      ||
	         nodeType == ATTRIBUTE_NODE         ||
		     nodeType == ENTITY_NODE            ||
		     nodeType == ENTITY_REFERENCE_NODE  ||
		     nodeType == DOCUMENT_FRAGMENT_NODE)
		{
		for (NodePtr n = getFirstChild() ; n.get() ;
		     n=n->getNextSibling() )
		    {
            if (n->getNodeType() != COMMENT_NODE &&
		        n->getNodeType() != COMMENT_NODE)
                buf.append(n->getTextContent());
		    }
		}
    return buf;
}
