Codegen_destroy(Codegen *c){
    g_assert(c);
    if(c->fp)
        fclose(c->fp);

    g_free(c->code_path);
    g_free(c->name);
    g_free(c);
    return;
    }
