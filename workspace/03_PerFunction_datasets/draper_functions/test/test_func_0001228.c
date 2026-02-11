sLadTlg_apply(sLadTlg *tlg)
{
    List *li;

    for (li = tlg->lad_list; li != NULL; li = li->next)
        sLad_make_region(li->data);

    for (li = tlg->lad_list; li != NULL; li = li->next) {
        if (verbose_level > 0)
            fprintf(stderr, "## loop-aligned decomps ##\n");
        sLad_apply(li->data);
    }
}
