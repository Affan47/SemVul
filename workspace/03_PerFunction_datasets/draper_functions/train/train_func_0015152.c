xmlSchemaIDCFreeMatcherList(xmlSchemaIDCMatcherPtr matcher)
{
    xmlSchemaIDCMatcherPtr next;

    while (matcher != NULL) {
        next = matcher->next;
        if (matcher->keySeqs != NULL) {
            int i;
            for (i = 0; i < matcher->sizeKeySeqs; i++)
                if (matcher->keySeqs[i] != NULL)
                    xmlFree(matcher->keySeqs[i]);
            xmlFree(matcher->keySeqs);
        }
        if (matcher->targets != NULL) {
            if (matcher->idcType == XML_SCHEMA_TYPE_IDC_KEYREF) {
                int i;
                xmlSchemaPSVIIDCNodePtr idcNode;


                for (i = 0; i < matcher->targets->nbItems; i++) {
                    idcNode =
                        (xmlSchemaPSVIIDCNodePtr) matcher->targets->items[i];
                    xmlFree(idcNode->keys);
                    xmlFree(idcNode);
                }
            }
            xmlSchemaItemListFree(matcher->targets);
        }
        xmlFree(matcher);
        matcher = next;
    }
}
