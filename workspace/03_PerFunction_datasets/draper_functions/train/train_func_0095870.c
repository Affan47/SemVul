hdmv_vm_get_uo_mask(HDMV_VM *p)
{
    uint32_t     mask = 0;
    MOBJ_OBJECT *o    = NULL;

    bd_mutex_lock(&p->mutex);

    if ((o = p->object ? p->object : (p->playing_object ? p->playing_object : p->suspended_object))) {
        mask |= o->menu_call_mask;
        mask |= o->title_search_mask << 1;
    }

    bd_mutex_unlock(&p->mutex);
    return mask;
}
