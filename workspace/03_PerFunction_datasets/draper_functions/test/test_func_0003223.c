dfb_window_set_key_selection( CoreWindow                    *window,
                              DFBWindowKeySelection          selection,
                              const DFBInputDeviceKeySymbol *keys,
                              unsigned int                   num_keys )
{
    DFBResult         ret;
    CoreWindowConfig  config;
    CoreWindowStack  *stack = window->stack;

    D_ASSERT( selection == DWKS_ALL || selection == DWKS_NONE || selection == DWKS_LIST );
    D_ASSERT( keys != NULL || selection != DWKS_LIST );
    D_ASSERT( num_keys > 0 || selection != DWKS_LIST );


    if (dfb_windowstack_lock( stack ))
         return DFB_FUSION;


    if (DFB_WINDOW_DESTROYED( window )) {
         dfb_windowstack_unlock( stack );
         return DFB_DESTROYED;
    }

    config.key_selection = selection;
    config.keys          = (DFBInputDeviceKeySymbol*) keys;
    config.num_keys      = num_keys;

    ret = dfb_wm_set_window_config( window, &config, CWCF_KEY_SELECTION );


    dfb_windowstack_unlock( stack );

    return ret;
}
