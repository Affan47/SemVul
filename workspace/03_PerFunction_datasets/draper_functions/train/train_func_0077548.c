xmlSchemaCustomWarning(xmlSchemaAbstractCtxtPtr actxt,
                   xmlParserErrors error,
                   xmlNodePtr node,
                   xmlSchemaTypePtr type ATTRIBUTE_UNUSED,
                   const char *message,
                   const xmlChar *str1,
                   const xmlChar *str2,
                   const xmlChar *str3)
{
    xmlChar *msg = NULL;

    xmlSchemaFormatNodeForError(&msg, actxt, node);
    msg = xmlStrcat(msg, (const xmlChar *) message);
    msg = xmlStrcat(msg, BAD_CAST ".\n");


    xmlSchemaErr4Line(actxt, XML_ERR_WARNING, error, node, 0,
        (const char *) msg, str1, str2, str3, NULL);

    FREE_AND_NULL(msg)
}
