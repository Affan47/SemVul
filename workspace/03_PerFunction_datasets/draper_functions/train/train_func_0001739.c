graph_walk(graph_ty *gp)
{
    int             nproc;
    string_ty       *key;
    string_ty       *s;
    id_ty           *idp;
    string_list_ty  wl;
    opcode_context_ty *ocp;


    key = str_from_c("parallel_jobs");
    ocp = opcode_context_new(0, 0);
    idp = opcode_context_id_search(ocp, key);


    nproc = 1;
    if (idp)
    {
        id_variable_query(idp, &wl);
        if (wl.nstrings == 1)
        {
            nproc = atoi(wl.string[0]->str_text);
            if (nproc < 1)
                nproc = 1;
        }
        string_list_destructor(&wl);
    }


    string_list_constructor(&wl);
    s = str_format("%d", nproc);
    string_list_append(&wl, s);
    str_free(s);
    opcode_context_id_assign(ocp, key, id_variable_new(&wl), 0);
    string_list_destructor(&wl);
    str_free(key);
    opcode_context_delete(ocp);


    return graph_walk_inner(gp, graph_recipe_run, nproc);
}
