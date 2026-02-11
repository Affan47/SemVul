domRemoveFromMap(AjPDomNodeList list, const AjPDomNode key)
{
    AjPDomNode trukey;

    if(!list->table)
        return;


    ajTableRemoveKey(list->table, key, (void **) &trukey);

    return;
}
