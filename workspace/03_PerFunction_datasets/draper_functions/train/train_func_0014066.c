xmlSchemaAnnotDump(FILE * output, xmlSchemaAnnotPtr annot)
{
    xmlChar *content;

    if (annot == NULL)
        return;

    content = xmlNodeGetContent(annot->content);
    if (content != NULL) {
        fprintf(output, "  Annot: %s\n", content);
        xmlFree(content);
    } else
        fprintf(output, "  Annot: empty\n");
}
