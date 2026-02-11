apply(ast_sent* s) {
        if (s->get_nodetype() == AST_FOREACH) {


            ast_foreach* fe = (ast_foreach*) s;
            ast_expr *e = fe->get_filter();
            if (e == NULL) return true;

            ast_sent *old_body = fe->get_body();
            ast_sent* new_body = make_if_then(old_body, e);
            ast_sentblock* sb = ast_sentblock::new_sentblock();
            sb->add_sent(new_body);

            fe->set_filter(NULL);
            fe->set_body(sb);
        } else if (s->get_nodetype() == AST_BFS) {
            ast_bfs* bfs = (ast_bfs*) s;
            ast_expr* e = bfs->get_f_filter();
            if (e != NULL) {
                ast_sent *old_body = bfs->get_fbody();
                ast_sent* new_body = make_if_then(old_body, e);
                ast_sentblock* sb = ast_sentblock::new_sentblock();
                sb->add_sent(new_body);

                bfs->set_f_filter(NULL);
                bfs->set_fbody(sb);
            }
            e = bfs->get_b_filter();
            if (e != NULL) {
                ast_sent *old_body = bfs->get_bbody();
                ast_sent* new_body = make_if_then(old_body, e);
                ast_sentblock* sb = ast_sentblock::new_sentblock();
                sb->add_sent(new_body);

                bfs->set_b_filter(NULL);
                bfs->set_bbody(sb);
            }


        }
        return true;
    }
