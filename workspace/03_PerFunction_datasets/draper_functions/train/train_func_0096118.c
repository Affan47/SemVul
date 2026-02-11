apply(ast_sent *s) {
        if (s->get_nodetype() == AST_FOREACH) {
            ast_foreach* fe = (ast_foreach*) s;
            if (gm_is_iteration_use_reverse(fe->get_iter_type())) {
                target_graph = fe->get_iterator()->getTypeInfo()->get_target_graph_sym();
                r_edge = true;
            }
        }
        return true;
    }
