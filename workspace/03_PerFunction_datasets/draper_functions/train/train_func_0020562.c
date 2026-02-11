xmlC14NPrintAttrs(const xmlAttrPtr attr, xmlC14NCtxPtr ctx)
{
    xmlChar *value;
    xmlChar *buffer;

    if ((attr == NULL) || (ctx == NULL)) {
        xmlC14NErrParam("writing attributes");
        return (0);
    }

    xmlOutputBufferWriteString(ctx->buf, " ");
    if (attr->ns != NULL && xmlStrlen(attr->ns->prefix) > 0) {
        xmlOutputBufferWriteString(ctx->buf,
                                   (const char *) attr->ns->prefix);
        xmlOutputBufferWriteString(ctx->buf, ":");
    }
    xmlOutputBufferWriteString(ctx->buf, (const char *) attr->name);
    xmlOutputBufferWriteString(ctx->buf, "=\"");

    value = xmlNodeListGetString(attr->doc, attr->children, 1);

    if (value != NULL) {
        buffer = xmlC11NNormalizeAttr(value);
        xmlFree(value);
        if (buffer != NULL) {
            xmlOutputBufferWriteString(ctx->buf, (const char *) buffer);
            xmlFree(buffer);
        } else {
            xmlC14NErrInternal("normalizing attributes axis");
            return (0);
        }
    }
    xmlOutputBufferWriteString(ctx->buf, "\"");
    return (1);
}
