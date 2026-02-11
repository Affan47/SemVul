DestroyWMSMiniDriverManager()

{
    CPLMutexHolderD(&g_mini_driver_manager_mutex);

    if( g_mini_driver_manager != 0 )
    {
        delete g_mini_driver_manager;
        g_mini_driver_manager = NULL;
    }
}
