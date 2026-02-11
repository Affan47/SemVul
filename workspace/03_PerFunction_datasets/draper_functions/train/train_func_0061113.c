globus_l_openssl_deactivate(void)
{
    int                                 i;

    OBJ_cleanup();

    ERR_clear_error();

    X509V3_EXT_cleanup();

    if (CRYPTO_get_id_callback() == globus_l_openssl_thread_id)
    {
        CRYPTO_set_id_callback(NULL);
    }
    if (CRYPTO_get_locking_callback() == globus_l_openssl_locking_cb)
    {
        CRYPTO_set_locking_callback(NULL);
    }

    for (i=0; i<CRYPTO_num_locks(); i++)
    {
        globus_mutex_destroy(&(mutex_pool[i]));
    }

    free(mutex_pool);

    globus_module_deactivate(GLOBUS_GSI_OPENSSL_ERROR_MODULE);
    globus_module_deactivate(GLOBUS_COMMON_MODULE);

    return GLOBUS_SUCCESS;
}
