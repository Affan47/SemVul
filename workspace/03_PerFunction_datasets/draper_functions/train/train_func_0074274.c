is_it_a_leaf(symtab_ty *stp, string_ty *filename, void *data, void *aux)
{
    graph_file_ty   *gfp;
    graph_recipe_list_nrc_ty *walk;

    (void)stp;
    (void)filename;
    gfp = data;
    gfp->done = 0;
    gfp->input_satisfied = 0;
    gfp->input_uptodate = 0;

    walk = aux;
    if
    (
        gfp->input->nrecipes == 0
    &&
        gfp->output->nrecipes != 0
    &&
        !gfp->previous_error
    &&
        !gfp->previous_backtrack
    )
    {
        trace(("leaf file \"%s\"\n", filename->str_text));
        implications_of_file(walk, gfp, 1);
        star_as_specified('#');
    }
}
