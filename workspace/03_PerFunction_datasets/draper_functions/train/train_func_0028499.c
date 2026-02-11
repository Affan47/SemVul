alloc_margin(line_list * ll)
{   margin *m;

    if (ll->free_margin_list != 0) {
        m = ll->free_margin_list;
        ll->free_margin_list = ll->free_margin_list->next;
    } else if (ll->local_margin_alloc_count < MAX_LOCAL_ACTIVE) {
        m = ll->local_margins + ll->local_margin_alloc_count;
        ++ ll->local_margin_alloc_count;
    } else {
        m = gs_alloc_struct(ll->memory, margin, &st_margin, "filling contiguity margin");


    }
    return m;
}
