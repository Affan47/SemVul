gm_get_default_graph(gm_symtab* symTab) {
    int foundCount = 0;
    ast_id* targetGraph = NULL;
    do {
        std::set<gm_symtab_entry*> entries = symTab->get_entries();
        for (std::set<gm_symtab_entry*>::iterator II = entries.begin(); II != entries.end(); II++) {
            ast_typedecl* entryType = (*II)->getType();
            if (entryType->is_graph()) {
                foundCount++;
                if (foundCount > 1) {
                    gm_type_error(GM_ERROR_DEFAULT_GRAPH_AMBIGUOUS, targetGraph, (*II)->getId());
                    return NULL;
                }
                targetGraph = (*II)->getId();
            }
        }
        symTab = symTab->get_parent();
    } while (symTab != NULL);
    return targetGraph;
}
