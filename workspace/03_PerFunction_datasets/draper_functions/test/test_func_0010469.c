apply(ast_sent* s) {
        if (s->get_nodetype() == AST_FOREACH) {
            depth++;
            ast_foreach* fe = (ast_foreach*) s;
            if (depth == 1) {
                if (gm_is_all_graph_node_iteration(fe->get_iter_type())) {
                    outer_loop = fe;
                    MAP[fe] = NULL;
                }
            } else if ((depth == 2) && (outer_loop != NULL)) {
                int iter = fe->get_iter_type();
                if (gm_is_in_nbr_node_iteration(fe->get_iter_type())
                    || gm_is_out_nbr_node_iteration(fe->get_iter_type())) {
                    MAP[fe] = outer_loop;
                }
            }
        }
        return true;
    }
