orte_iof_base_write_event_construct(orte_iof_write_event_t* wev)
{
    wev->pending = false;
    wev->fd = -1;
    OBJ_CONSTRUCT(&wev->outputs, opal_list_t);
    wev->ev = opal_event_alloc();
}
