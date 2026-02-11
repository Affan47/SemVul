xmlSchemaGetComponentName(xmlSchemaBasicItemPtr item)
{
    switch (item->type) {
        case XML_SCHEMA_TYPE_ELEMENT:
            return (((xmlSchemaElementPtr) item)->name);
        case XML_SCHEMA_TYPE_ATTRIBUTE:
            return (((xmlSchemaAttributePtr) item)->name);
        case XML_SCHEMA_TYPE_ATTRIBUTEGROUP:
            return (((xmlSchemaAttributeGroupPtr) item)->name);
        case XML_SCHEMA_TYPE_BASIC:
        case XML_SCHEMA_TYPE_SIMPLE:
        case XML_SCHEMA_TYPE_COMPLEX:
            return (((xmlSchemaTypePtr) item)->name);
        case XML_SCHEMA_TYPE_GROUP:
            return (((xmlSchemaModelGroupDefPtr) item)->name);
        case XML_SCHEMA_TYPE_IDC_KEY:
        case XML_SCHEMA_TYPE_IDC_UNIQUE:
        case XML_SCHEMA_TYPE_IDC_KEYREF:
            return (((xmlSchemaIDCPtr) item)->name);
        case XML_SCHEMA_TYPE_ATTRIBUTE_USE:
            if (WXS_ATTRUSE_DECL(item) != NULL) {
                return(xmlSchemaGetComponentName(
                    WXS_BASIC_CAST WXS_ATTRUSE_DECL(item)));
            } else
                return(NULL);
        case XML_SCHEMA_EXTRA_QNAMEREF:
            return (((xmlSchemaQNameRefPtr) item)->name);
        case XML_SCHEMA_TYPE_NOTATION:
            return (((xmlSchemaNotationPtr) item)->name);
        default:


            break;
    }
    return (NULL);
}
