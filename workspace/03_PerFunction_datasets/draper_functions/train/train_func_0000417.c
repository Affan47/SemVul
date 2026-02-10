in_construct(orte_filem_raw_incoming_t *ptr)
{
    ptr->app_idx = 0;
    ptr->pending = false;
    ptr->fd = -1;
    ptr->file = NULL;
    ptr->top = NULL;
    ptr->fullpath = NULL;
    ptr->link_pts = NULL;
    OBJ_CONSTRUCT(&ptr->outputs, opal_list_t);
}
