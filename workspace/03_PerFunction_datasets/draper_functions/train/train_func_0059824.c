globus_l_sge_module_deactivate(void)
{
    globus_mutex_lock(&globus_l_sge_mutex);
    shutdown_called = GLOBUS_TRUE;

    while (callback_count > 0)
    {
	globus_cond_wait(&globus_l_sge_cond, &globus_l_sge_mutex);
    }
    globus_mutex_unlock(&globus_l_sge_mutex);

    GlobusDebugDestroy(SEG_SGE);

    globus_module_deactivate(GLOBUS_COMMON_MODULE);

    return 0;
}
