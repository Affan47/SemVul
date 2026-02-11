apply(ast_expr* e) {
        if (e->is_builtin()) {
            ast_expr_builtin* b = (ast_expr_builtin*) e;
            if ((b->get_driver() != NULL) && (b->get_driver()->getSymInfo() == sym)) contain = true;
        }
        return true;
    }
