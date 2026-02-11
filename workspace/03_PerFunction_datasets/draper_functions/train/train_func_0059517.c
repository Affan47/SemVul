setAttributeNode(AttrPtr attr)
                      throw(DOMException)
{
    attributes.setNamedItem(attr);
    return attr;
}
