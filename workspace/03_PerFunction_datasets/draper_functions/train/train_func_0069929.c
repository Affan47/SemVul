checkAndSetBoundGraphsForMap(ast_mapaccess* mapAccess) {
        ast_maptypedecl* mapDecl = (ast_maptypedecl*) mapAccess->get_map_id()->getTypeInfo();
        ast_typedecl* keyType = mapDecl->get_key_type();
        ast_typedecl* valueType = mapDecl->get_value_type();
        if (gm_requires_target_graph_type(keyType->getTypeSummary())) {
            gm_symtab_entry* keyGraph = keyType->get_target_graph_sym();
            mapAccess->set_bound_graph_for_key(keyGraph);
        }
        if (gm_requires_target_graph_type(valueType->getTypeSummary())) {
            gm_symtab_entry* valueGraph = valueType->get_target_graph_sym();
            mapAccess->set_bound_graph_for_value(valueGraph);
        }
    }
