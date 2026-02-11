unique_device_connect( UniqueDevice    *device,
                       CoreInputDevice *source )
{
     DFBResult         ret;
     WMShared         *shared;
     UniqueContext    *context;
     DeviceConnection *connection;

     D_MAGIC_ASSERT( device, UniqueDevice );

     D_ASSERT( source != NULL );

     D_ASSERT( device->clazz >= 0 );
     D_ASSERT( device->clazz < MAX_CLASSES );
     D_ASSERT( classes[device->clazz] != NULL );

     context = device->context;

     D_MAGIC_ASSERT( context, UniqueContext );

     shared = context->shared;

     D_MAGIC_ASSERT( shared, WMShared );

     D_DEBUG_AT( UniQuE_Device, "unique_device_connect( %p, %p, ID %d )\n",
                 device, source, dfb_input_device_id( source ) );


     connection = SHCALLOC( context->shmpool, 1, sizeof(DeviceConnection) );
     if (!connection)
          return D_OOSHM();


     connection->source = dfb_input_device_id( source );


     ret = dfb_input_attach_global( source, shared->device_listener,
                                    device, &connection->reaction );
     if (ret) {
          SHFREE( context->shmpool, connection );
          return ret;
     }


     direct_list_append( &device->connections, &connection->link );

     D_MAGIC_SET( connection, DeviceConnection );

     if (classes[device->clazz]->Connected)
          classes[device->clazz]->Connected( device, device->data, device->ctx, source );

     return DFB_OK;
}
