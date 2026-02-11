parent_already_added(ast_expr* e) {
        e = e->get_up_op();
        while (e != NULL) {
            if (sub_exprs[current_fe].find(e) != sub_exprs[current_fe].end()) {
                return true;
            }
            e = e->get_up_op();
        }
        return false;
    }
