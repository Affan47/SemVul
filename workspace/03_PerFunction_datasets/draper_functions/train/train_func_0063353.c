xmlnode_hide_attrib(xmlnode parent, const char *name)
{
    xmlnode attrib;

    if(parent == NULL || parent->firstattrib == NULL || name == NULL)
        return;

    attrib = _xmlnode_search(parent->firstattrib, name, NTYPE_ATTRIB);
    if(attrib == NULL)
        return;


    _xmlnode_hide_sibling(attrib);


    if(parent->firstattrib == attrib)
        parent->firstattrib = attrib->next;
    if(parent->lastattrib == attrib)
        parent->lastattrib = attrib->prev;
}
