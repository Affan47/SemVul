graph_file_list_destructor(graph_file_list_ty *gflp)
{
    size_t          j;

    trace(("graph_file_list_destructor(gflp = %p)\n{\n", gflp));
    for (j = 0; j < gflp->nfiles; ++j)
        graph_file_delete(gflp->item[j].file);
    if (gflp->item)
        mem_free(gflp->item);
    gflp->nfiles = 0;
    gflp->nfiles_max = 0;
    gflp->item = 0;
    trace(("}\n"));
}
