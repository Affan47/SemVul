unique_device_destroy( UniqueDevice *device )
{
     DirectLink              *n;
     DeviceConnection        *connection;
     UniqueContext           *context;
     const UniqueDeviceClass *clazz;

     D_MAGIC_ASSERT( device, UniqueDevice );

     context = device->context;

     D_MAGIC_ASSERT( context, UniqueContext );

     D_ASSERT( device->clazz >= 0 );
     D_ASSERT( device->clazz < MAX_CLASSES );

     clazz = classes[device->clazz];

     D_ASSERT( clazz != NULL );

     D_DEBUG_AT( UniQuE_Device, "unique_device_destroy( %p )\n", device );

     direct_list_foreach_safe (connection, n, device->connections) {
          D_MAGIC_ASSERT( connection, DeviceConnection );

          purge_connection( device, connection );
     }

     D_ASSERT( device->connections == NULL );

     if (clazz->Shutdown)
          clazz->Shutdown( device, device->data, device->ctx );

     fusion_reactor_free( device->reactor );

     if (device->data)
          SHFREE( context->shmpool, device->data );

     D_MAGIC_CLEAR( device );

     SHFREE( context->shmpool, device );

     return DFB_OK;
}
