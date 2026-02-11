reload_keymap( CoreInputDevice *device )
{
     int                i;
     InputDeviceShared *shared;

     D_DEBUG_AT( Core_Input, "%s( %p )\n", __FUNCTION__, device );

     D_MAGIC_ASSERT( device, CoreInputDevice );

     shared = device->shared;

     D_ASSERT( shared != NULL );

     if (shared->device_info.desc.min_keycode < 0 ||
         shared->device_info.desc.max_keycode < 0)
          return DFB_UNSUPPORTED;


     for (i=0; i<shared->keymap.num_entries; i++)
          shared->keymap.entries[i].code = -1;


     for (i=shared->keymap.min_keycode; i<=shared->keymap.max_keycode; i++)
          get_keymap_entry( device, i );

     D_INFO( "DirectFB/Input: Reloaded keymap for '%s' [0x%02x]\n",
             shared->device_info.desc.name, shared->id );

     return DFB_OK;
}
