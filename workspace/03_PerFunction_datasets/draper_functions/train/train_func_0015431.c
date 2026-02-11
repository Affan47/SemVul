globus_libc_initgroups(
    char *                              username,
    gid_t                               gid)
{
    int                                 rc;
    int                                 tmprc = 0;

#ifndef BUILD_LITE

    globus_l_libc_initgroups_info_t *   info;
    int                                 i;
    int                                 threads;
    char *                              tmp;

    threads = 2;
    if((tmp = globus_module_getenv("GLOBUS_CALLBACK_POLLING_THREADS")) != NULL)
    {
        rc = atoi(tmp);
        if(rc > 0)
        {
            threads = rc;
        }
    }

    info = (globus_l_libc_initgroups_info_t *)
        globus_malloc(sizeof(globus_l_libc_initgroups_info_t));

    globus_mutex_init(&info->mutex, NULL);
    globus_cond_init(&info->cond, NULL);

    info->count = 0;
    info->username = username;
    info->gid = gid;
    info->rc = 0;
    globus_mutex_lock(&info->mutex);
    {
        for(i = 0; i < threads; i++)
        {
            globus_callback_register_oneshot(
                NULL,
                NULL,
                globus_l_libc_initgroups_cb,
                info);
            info->count++;
        }

        while(info->count > 0)
        {
            globus_cond_wait(&info->cond, &info->mutex);
        }
    }
    globus_mutex_unlock(&info->mutex);

    tmprc = info->rc;
    globus_mutex_destroy(&info->mutex);
    globus_cond_destroy(&info->cond);
    globus_free(info);

#endif

    rc = initgroups(username, gid);
    if(!rc && tmprc)
    {
        rc = tmprc;
    }

    return rc;
}
