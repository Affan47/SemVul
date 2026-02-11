opal_shmem_unlink(opal_shmem_ds_t *ds_buf)
{
    if (!opal_shmem_base_selected) {
        return OPAL_ERROR;
    }

    return opal_shmem_base_module->unlink(ds_buf);
}
