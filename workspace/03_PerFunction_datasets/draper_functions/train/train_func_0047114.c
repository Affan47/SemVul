k5_cc_mutex_force_unlock(k5_cc_mutex *m)
{
    m->refcount = 0;
    m->owner = NULL;
    if (m->refcount > 0) {
        k5_mutex_unlock(&m->lock);
    }
}
