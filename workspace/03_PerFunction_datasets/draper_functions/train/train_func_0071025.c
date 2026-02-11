jtrk_cons(local_jobtracker_t *ptr)
{
    ptr->cmd = NULL;
    OBJ_CONSTRUCT(&ptr->apps, opal_pointer_array_t);
    opal_pointer_array_init(&ptr->apps, 1, INT_MAX, 1);
    ptr->napps = 0;
}
