access_pattern_list_to_template_list_set_list(List *a_ptn_list)
{
    List *l, *ret = NULL;

    for (l = a_ptn_list; l != NULL; l = l->next) {
        Access_pattern *ap = l->data;
        Template_list_set *tl_set;

        tl_set = search_template_list_set(ap, ret);
        if(tl_set == NULL) {
            tl_set = make_template_list_set(ap);
            ret = list_prepend(ret, tl_set);
        } else {
            Template *t = search_template(ap, tl_set->template_list);
            if(t == NULL) {
                t = construct_template(ap);
                tl_set->template_list
                    = list_prepend(tl_set->template_list, t);
            } else {
                add1_IntSet(t->entry_set, ap->entry);
            }
        }
    }
    return ret;
}
