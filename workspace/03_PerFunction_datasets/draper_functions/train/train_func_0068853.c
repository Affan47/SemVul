ws_pragma_meta_body(WsCompilerPtr compiler,
                                      WsUtf8String *property_name,
                                      WsUtf8String *content,
                                      WsUtf8String *scheme)
{
    WsPragmaMetaBody *mb = ws_calloc(1, sizeof(*mb));

    if (mb == NULL) {
        ws_error_memory(compiler);
        return NULL;
    }

    mb->property_name = property_name;
    mb->content = content;
    mb->scheme = scheme;

    return mb;
}
