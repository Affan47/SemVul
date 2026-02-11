hasAttribute(const DSRXMLCursor &cursor,
                                    const char *name) const
{
    OFBool result = OFFalse;
    if (cursor.Node != NULL)
    {

        if ((name != NULL) && (strlen(name) > 0))
            result = (xmlHasProp(cursor.Node, OFreinterpret_cast(const xmlChar *, name)) != NULL);
    }
    return result;
}
