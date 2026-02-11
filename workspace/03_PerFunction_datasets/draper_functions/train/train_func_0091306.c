apply(ast_sent *s) {
        if (s->get_nodetype() == AST_BFS) {
            gm_backend_error(GM_ERROR_GPS_UNSUPPORTED_OP, s->get_line(), s->get_col(), "BFS or DFS");
            _error = true;
        }

        if (s->get_nodetype() == AST_RETURN) {
            if (foreach_depth > 0) {
                gm_backend_error(GM_ERROR_GPS_UNSUPPORTED_OP, s->get_line(), s->get_col(), "Return inside foreach");
                _error = true;
            }
        }

        if (s->get_nodetype() == AST_FOREACH) {
            foreach_depth++;
        }

        return true;
    }
