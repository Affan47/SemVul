unique_wm_module_init( CoreDFB *core, WMData *data, WMShared *shared, bool master )
{
     DFBResult ret;

     D_DEBUG_AT( UniQuE_WM, "unique_wm_init( core %p, data %p, shared %p, %s )\n",
                 core, data, shared, master ? "master" : "slave" );

     D_ASSERT( core != NULL );
     D_ASSERT( data != NULL );
     D_ASSERT( data->context_notify != NULL );
     D_ASSERT( data->window_notify != NULL );

     D_MAGIC_ASSERT( shared, WMShared );

     D_ASSERT( dfb_core == NULL );
     D_ASSERT( wm_data == NULL );
     D_ASSERT( wm_shared == NULL );

     if (data->module_abi != UNIQUE_WM_ABI_VERSION) {
          D_ERROR( "UniQuE/WM: Module ABI version (%d) does not match %d!\n",
                   data->module_abi, UNIQUE_WM_ABI_VERSION );
          return DFB_VERSIONMISMATCH;
     }

     ret = register_region_classes( shared, master );
     if (ret)
          return ret;

     ret = register_device_classes( shared, master );
     if (ret)
          goto error_device;

     if (master) {
          int i;

          ret = load_foo( core, shared );
          if (ret)
               goto error_foo;

          ret = dfb_input_add_global( _unique_device_listener, &shared->device_listener );
          if (ret)
               goto error_global;

          shared->context_pool    = unique_context_pool_create( data->world );
          shared->decoration_pool = unique_decoration_pool_create( data->world );
          shared->window_pool     = unique_window_pool_create( data->world );

          shared->insets.l = foo[UFI_W].rect.w;
          shared->insets.t = foo[UFI_N].rect.h;
          shared->insets.r = foo[UFI_E].rect.w;
          shared->insets.b = foo[UFI_S].rect.h;

          for (i=0; i<8; i++)
               shared->foo_rects[i] = foo[i].rect;
     }
     else
          dfb_input_set_global( _unique_device_listener, shared->device_listener );

     dfb_core  = core;
     wm_data   = data;
     wm_shared = shared;

     return DFB_OK;

error_global:
     unload_foo( shared );

error_foo:
     unregister_device_classes( shared );

error_device:
     unregister_region_classes( shared );

     return ret;
}
