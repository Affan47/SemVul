ompi_info_get_nthkey (ompi_info_t *info, int n, char *key)
{
    ompi_info_entry_t *iterator;


    OPAL_THREAD_LOCK(info->i_lock);
    for (iterator = (ompi_info_entry_t *)opal_list_get_first(&(info->super));
         n > 0;
         --n) {
         iterator = (ompi_info_entry_t *)opal_list_get_next(iterator);
         if (opal_list_get_end(&(info->super)) ==
             (opal_list_item_t *) iterator) {
             OPAL_THREAD_UNLOCK(info->i_lock);
             return MPI_ERR_ARG;
         }
    }


    strncpy(key, iterator->ie_key, MPI_MAX_INFO_KEY);
    OPAL_THREAD_UNLOCK(info->i_lock);
    return MPI_SUCCESS;
}
