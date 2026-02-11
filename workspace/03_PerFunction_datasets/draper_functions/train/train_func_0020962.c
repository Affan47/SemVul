UnlinkBoolAttributeInMarkup(HTML_MARKUP *htmlMarkup, const char *name)
{
    HTML_ATTRIBUTE **attribPtr, *attrib;

    assert(htmlMarkup != NULL);

    if((attribPtr = FindMarkupAttribute(htmlMarkup, name)) == NULL)
    {
        return FALSE;
    }

    attrib = *attribPtr;


    if (attrib->value != NULL)
        return FALSE;

    *attribPtr = attrib->next;
    attrib->next = NULL;
    FreeMemory(attrib->name);
    if (attrib->whitespace)
        FreeMemory(attrib->whitespace);
    FreeMemory(attrib);

    return TRUE;
}
