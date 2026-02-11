xmlRelaxNGGenerateAttributes(xmlRelaxNGParserCtxtPtr ctxt,
                             xmlRelaxNGDefinePtr def)
{
    xmlRelaxNGDefinePtr parent, cur, tmp;


    if (ctxt->nbErrors != 0)
        return (-1);

    parent = NULL;
    cur = def;
    while (cur != NULL) {
        if ((cur->type == XML_RELAXNG_ELEMENT) ||
            (cur->type == XML_RELAXNG_TEXT) ||
            (cur->type == XML_RELAXNG_DATATYPE) ||
            (cur->type == XML_RELAXNG_PARAM) ||
            (cur->type == XML_RELAXNG_LIST) ||
            (cur->type == XML_RELAXNG_VALUE) ||
            (cur->type == XML_RELAXNG_EMPTY))
            return (0);
        if ((cur->type == XML_RELAXNG_CHOICE) ||
            (cur->type == XML_RELAXNG_INTERLEAVE) ||
            (cur->type == XML_RELAXNG_GROUP) ||
            (cur->type == XML_RELAXNG_ONEORMORE) ||
            (cur->type == XML_RELAXNG_ZEROORMORE) ||
            (cur->type == XML_RELAXNG_OPTIONAL) ||
            (cur->type == XML_RELAXNG_PARENTREF) ||
            (cur->type == XML_RELAXNG_EXTERNALREF) ||
            (cur->type == XML_RELAXNG_REF) ||
            (cur->type == XML_RELAXNG_DEF)) {
            if (cur->content != NULL) {
                parent = cur;
                cur = cur->content;
                tmp = cur;
                while (tmp != NULL) {
                    tmp->parent = parent;
                    tmp = tmp->next;
                }
                continue;
            }
        }
        if (cur == def)
            break;
        if (cur->next != NULL) {
            cur = cur->next;
            continue;
        }
        do {
            cur = cur->parent;
            if (cur == NULL)
                break;
            if (cur == def)
                return (1);
            if (cur->next != NULL) {
                cur = cur->next;
                break;
            }
        } while (cur != NULL);
    }
    return (1);
}
