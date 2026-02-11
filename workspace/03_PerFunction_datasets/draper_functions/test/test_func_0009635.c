new_builtin_expr(ast_id* id, gm_builtin_def* d, expr_list* t) {
    ast_expr_builtin* E = new ast_expr_builtin();
    E->expr_class = GMEXPR_BUILTIN;
    E->driver = id;
    if (id != NULL) id->set_parent(E);
    E->def = d;
    E->orgname = gm_strdup(d->get_orgname());
    if (t != NULL) {
        E->args = t->LIST;

        std::list<ast_expr*>::iterator I;
        for (I = E->args.begin(); I != E->args.end(); I++)
            (*I)->set_parent(E);
        delete t;
    }
    return E;
}
