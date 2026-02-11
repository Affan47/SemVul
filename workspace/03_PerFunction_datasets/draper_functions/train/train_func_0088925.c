ws_variable_define(WsCompilerPtr compiler, WsUInt32 line,
                                WsBool variablep, char *name)
{
    WsNamespace *ns;


    ns = ws_hash_get(compiler->variables_hash, name);
    if (ns) {
        ws_src_error(compiler, line, "redeclaration of `%s'", name);
        ws_src_error(compiler, ns->line, "`%s' previously declared here", name);
        return NULL;
    }


    if (compiler->next_vindex > 255) {

        ws_src_error(compiler, line, "too many local variables");
        return NULL;
    }

    ns = ws_calloc(1, sizeof(*ns));
    if (ns == NULL) {
        ws_error_memory(compiler);
        return NULL;
    }

    ns->line = line;
    ns->vindex = compiler->next_vindex++;

    if (!ws_hash_put(compiler->variables_hash, name, ns)) {
        ws_free(ns);
        ws_error_memory(compiler);
        return NULL;
    }

    return ns;
}
