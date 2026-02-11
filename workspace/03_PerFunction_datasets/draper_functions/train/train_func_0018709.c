ChangeAttributeValue(HTML_ATTRIBUTE *htmlAttribute, char *value,
                          int quotes)
{
    assert(htmlAttribute != NULL);


    if(htmlAttribute->value != NULL)
    {
        FreeMemory(htmlAttribute->value);
        htmlAttribute->value = NULL;
    }

    htmlAttribute->value = value;
    htmlAttribute->quotes = quotes;

    return TRUE;
}
