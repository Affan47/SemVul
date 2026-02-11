dfb_input_device_reload_keymap( CoreInputDevice *device )
{
     int                ret;
     InputDeviceShared *shared;

     D_MAGIC_ASSERT( device, CoreInputDevice );

     shared = device->shared;

     D_ASSERT( shared != NULL );

     D_INFO( "DirectFB/Input: Reloading keymap for '%s' [0x%02x]...\n",
             shared->device_info.desc.name, shared->id );

     if (fusion_call_execute( &shared->call, FCEF_NONE, CIDC_RELOAD_KEYMAP, NULL, &ret ))
          return DFB_FUSION;

     return ret;
}
