lock(Timerset *set)
{
    gw_assert(set != NULL);
    mutex_lock(set->mutex);
}
