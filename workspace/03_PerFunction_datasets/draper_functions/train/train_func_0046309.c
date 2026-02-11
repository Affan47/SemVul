dfb_screens_hook_primary( CoreGraphicsDevice  *device,
                          void                *driver_data,
                          ScreenFuncs         *funcs,
                          ScreenFuncs         *primary_funcs,
                          void               **primary_driver_data )
{
     int         i;
     int         entries;
     CoreScreen *primary = screens[0];

     D_ASSERT( primary != NULL );
     D_ASSERT( device != NULL );
     D_ASSERT( funcs != NULL );


     if (primary_funcs)
          direct_memcpy( primary_funcs, primary->funcs, sizeof(ScreenFuncs) );


     if (primary_driver_data)
          *primary_driver_data = primary->driver_data;


     entries = sizeof(ScreenFuncs) / sizeof(void(*)( void ));
     for (i=0; i<entries; i++) {
          AnyFunc *newfuncs = (AnyFunc*) funcs;
          AnyFunc *oldfuncs = (AnyFunc*) primary->funcs;

          if (newfuncs[i])
               oldfuncs[i] = newfuncs[i];
     }


     primary->device      = device;
     primary->driver_data = driver_data;

     return primary;
}
