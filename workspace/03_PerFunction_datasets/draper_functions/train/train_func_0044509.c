nav_title_close(NAV_TITLE *title)
{
    unsigned ii, ss;

    for (ss = 0; ss < title->sub_path_count; ss++) {
        for (ii = 0; ii < title->sub_path[ss].clip_list.count; ii++) {
            clpi_free(title->sub_path[ss].clip_list.clip[ii].cl);
        }
        X_FREE(title->sub_path[ss].clip_list.clip);
    }
    X_FREE(title->sub_path);

    for (ii = 0; ii < title->pl->list_count; ii++) {
        clpi_free(title->clip_list.clip[ii].cl);
    }
    mpls_free(title->pl);
    X_FREE(title->clip_list.clip);
    X_FREE(title->root);
    X_FREE(title->chap_list.mark);
    X_FREE(title->mark_list.mark);
    X_FREE(title);
}
