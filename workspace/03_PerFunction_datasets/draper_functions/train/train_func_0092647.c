xmlSchemaComponentListFree(xmlSchemaItemListPtr list)
{
    if ((list == NULL) || (list->nbItems == 0))
        return;
    {
        xmlSchemaTreeItemPtr item;
        xmlSchemaTreeItemPtr *items = (xmlSchemaTreeItemPtr *) list->items;
        int i;

        for (i = 0; i < list->nbItems; i++) {
            item = items[i];
            if (item == NULL)
                continue;
            switch (item->type) {
                case XML_SCHEMA_TYPE_SIMPLE:
                case XML_SCHEMA_TYPE_COMPLEX:
                    xmlSchemaFreeType((xmlSchemaTypePtr) item);
                    break;
                case XML_SCHEMA_TYPE_ATTRIBUTE:
                    xmlSchemaFreeAttribute((xmlSchemaAttributePtr) item);
                    break;
                case XML_SCHEMA_TYPE_ATTRIBUTE_USE:
                    xmlSchemaFreeAttributeUse((xmlSchemaAttributeUsePtr) item);
                    break;
                case XML_SCHEMA_EXTRA_ATTR_USE_PROHIB:
                    xmlSchemaFreeAttributeUseProhib(
                        (xmlSchemaAttributeUseProhibPtr) item);
                    break;
                case XML_SCHEMA_TYPE_ELEMENT:
                    xmlSchemaFreeElement((xmlSchemaElementPtr) item);
                    break;
                case XML_SCHEMA_TYPE_PARTICLE:
                    if (item->annot != NULL)
                        xmlSchemaFreeAnnot(item->annot);
                    xmlFree(item);
                    break;
                case XML_SCHEMA_TYPE_SEQUENCE:
                case XML_SCHEMA_TYPE_CHOICE:
                case XML_SCHEMA_TYPE_ALL:
                    xmlSchemaFreeModelGroup((xmlSchemaModelGroupPtr) item);
                    break;
                case XML_SCHEMA_TYPE_ATTRIBUTEGROUP:
                    xmlSchemaFreeAttributeGroup(
                        (xmlSchemaAttributeGroupPtr) item);
                    break;
                case XML_SCHEMA_TYPE_GROUP:
                    xmlSchemaFreeModelGroupDef(
                        (xmlSchemaModelGroupDefPtr) item);
                    break;
                case XML_SCHEMA_TYPE_ANY:
                case XML_SCHEMA_TYPE_ANY_ATTRIBUTE:
                    xmlSchemaFreeWildcard((xmlSchemaWildcardPtr) item);
                    break;
                case XML_SCHEMA_TYPE_IDC_KEY:
                case XML_SCHEMA_TYPE_IDC_UNIQUE:
                case XML_SCHEMA_TYPE_IDC_KEYREF:
                    xmlSchemaFreeIDC((xmlSchemaIDCPtr) item);
                    break;
                case XML_SCHEMA_TYPE_NOTATION:
                    xmlSchemaFreeNotation((xmlSchemaNotationPtr) item);
                    break;
                case XML_SCHEMA_EXTRA_QNAMEREF:
                    xmlSchemaFreeQNameRef((xmlSchemaQNameRefPtr) item);
                    break;
                default: {

                    xmlSchemaPSimpleInternalErr(NULL,
                        "Internal error: xmlSchemaComponentListFree, "
                        "unexpected component type '%s'\n",
                        (const xmlChar *) WXS_ITEM_TYPE_NAME(item));
                         }
                    break;
            }
        }
        list->nbItems = 0;
    }
}
