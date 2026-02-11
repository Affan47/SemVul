process(ast_procdef* proc) {
    std::list<gm_symtab_entry*> S;
    std::list<ast_foreach*> F;
    bool b = find_deferred_writes(proc, S, F);
    if (b) {
        post_process_deferred_writes(S, F);

        gm_redo_rw_analysis(proc->get_body());
    }

    set_affected(b);
}
