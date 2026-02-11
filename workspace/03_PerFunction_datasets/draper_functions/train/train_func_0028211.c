setTextContent(const DOMString& text, int& ec)
{
    if (isReadOnly()) {
        ec = DOMException::NO_MODIFICATION_ALLOWED_ERR;
        return;
    }

    switch (nodeType()) {
        case Node::TEXT_NODE:
        case Node::CDATA_SECTION_NODE:
        case Node::COMMENT_NODE:
        case Node::PROCESSING_INSTRUCTION_NODE:
            setNodeValue(text, ec);
            break;
        case Node::ELEMENT_NODE:
        case Node::ATTRIBUTE_NODE:
        case Node::ENTITY_NODE:
        case Node::ENTITY_REFERENCE_NODE:
        case Node::DOCUMENT_FRAGMENT_NODE: {
            NodeBaseImpl *container = static_cast<NodeBaseImpl *>(this);

            container->removeChildren();

            if (!text.isEmpty())
                appendChild(document()->createTextNode(text.implementation()), ec);
            break;
        }
        case Node::DOCUMENT_NODE:
        case Node::DOCUMENT_TYPE_NODE:
        case Node::NOTATION_NODE:
        default:

            break;
    }
}
