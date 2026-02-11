initialize_data( CoreDFB *core, WMData *data, WMShared *shared )
{
     D_ASSERT( data != NULL );


     data->core       = core;
     data->world      = dfb_core_world( core );
     data->shared     = shared;
     data->module_abi = UNIQUE_WM_ABI_VERSION;


     data->context_notify = context_notify;
     data->window_notify  = window_notify;
}
