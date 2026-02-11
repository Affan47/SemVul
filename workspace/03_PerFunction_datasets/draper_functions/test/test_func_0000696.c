xmlSchemaParseAttributeGroupDefinition(xmlSchemaParserCtxtPtr pctxt,
                                       xmlSchemaPtr schema,
                                       xmlNodePtr node)
{
    const xmlChar *name;
    xmlSchemaAttributeGroupPtr ret;
    xmlNodePtr child = NULL;
    xmlAttrPtr attr;
    int hasRefs = 0;

    if ((pctxt == NULL) || (schema == NULL) || (node == NULL))
        return (NULL);

    attr = xmlSchemaGetPropNode(node, "name");
    if (attr == NULL) {
        xmlSchemaPMissingAttrErr(pctxt,
            XML_SCHEMAP_S4S_ATTR_MISSING,
            NULL, node, "name", NULL);
        return (NULL);
    }


    if (xmlSchemaPValAttrNode(pctxt,
        NULL, attr,
        xmlSchemaGetBuiltInType(XML_SCHEMAS_NCNAME), &name) != 0) {
        return (NULL);
    }
    ret = xmlSchemaAddAttributeGroupDefinition(pctxt, schema,
        name, pctxt->targetNamespace, node);
    if (ret == NULL)
        return (NULL);


    attr = node->properties;
    while (attr != NULL) {
        if (attr->ns == NULL) {
            if ((!xmlStrEqual(attr->name, BAD_CAST "name")) &&
                (!xmlStrEqual(attr->name, BAD_CAST "id")))
            {
                xmlSchemaPIllegalAttrErr(pctxt,
                    XML_SCHEMAP_S4S_ATTR_NOT_ALLOWED, NULL, attr);
            }
        } else if (xmlStrEqual(attr->ns->href, xmlSchemaNs)) {
            xmlSchemaPIllegalAttrErr(pctxt,
                XML_SCHEMAP_S4S_ATTR_NOT_ALLOWED, NULL, attr);
        }
        attr = attr->next;
    }

    xmlSchemaPValAttrID(pctxt, node, BAD_CAST "id");


    child = node->children;
    if (IS_SCHEMA(child, "annotation")) {
        ret->annot = xmlSchemaParseAnnotation(pctxt, child, 1);
        child = child->next;
    }


    if (xmlSchemaParseLocalAttributes(pctxt, schema, &child,
        (xmlSchemaItemListPtr *) &(ret->attrUses),
        XML_SCHEMA_TYPE_ATTRIBUTEGROUP, &hasRefs) == -1)
        return(NULL);
    if (hasRefs)
        ret->flags |= XML_SCHEMAS_ATTRGROUP_HAS_REFS;


    if (IS_SCHEMA(child, "anyAttribute")) {
        ret->attributeWildcard = xmlSchemaParseAnyAttribute(pctxt,
            schema, child);
        child = child->next;
    }
    if (child != NULL) {
        xmlSchemaPContentErr(pctxt,
            XML_SCHEMAP_S4S_ELEM_NOT_ALLOWED,
            NULL, node, child, NULL,
            "(annotation?, ((attribute | attributeGroup)*, anyAttribute?))");
    }
    return (ret);
}
