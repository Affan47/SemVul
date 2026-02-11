real_FE_list (panelmod_t *pan)
{
    int *list = gretl_list_copy(pan->pooled->list);
    int i;

    if (list != NULL) {

	for (i=2; i<=list[0]; i++) {
	    if (!in_gretl_list(pan->vlist, list[i])) {
		gretl_list_delete_at_pos(list, i--);
	    }
	}
    }

    return list;
}
