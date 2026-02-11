unique_device_create( CoreDFB              *core,
                      UniqueContext        *context,
                      UniqueDeviceClassID   class_id,
                      void                 *ctx,
                      UniqueDevice        **ret_device )
{
     DFBResult                ret;
     UniqueDevice            *device;
     const UniqueDeviceClass *clazz;

     D_DEBUG_AT( UniQuE_Device, "unique_device_create( class %d )\n", class_id );

     D_MAGIC_ASSERT( context, UniqueContext );

     D_ASSERT( class_id >= 0 );
     D_ASSERT( class_id < MAX_CLASSES );

     clazz = classes[class_id];

     D_ASSERT( clazz != NULL );
     D_ASSERT( ret_device != NULL );


     device = SHCALLOC( context->shmpool, 1, sizeof(UniqueDevice) );
     if (!device) {
          D_WARN( "out of (shared) memory" );
          return D_OOSHM();
     }


     device->context = context;
     device->clazz   = class_id;
     device->ctx     = ctx;


     if (clazz->data_size) {
          device->data = SHCALLOC( context->shmpool, 1, clazz->data_size );
          if (!device->data) {
               ret = D_OOSHM();
               goto error;
          }
     }


     device->reactor = fusion_reactor_new( sizeof(UniqueInputEvent),
                                           "UniQuE Device", dfb_core_world(core) );
     if (!device->reactor) {
          ret = DFB_FUSION;
          goto error;
     }

     fusion_reactor_set_lock( device->reactor, &context->stack->context->lock );

     D_MAGIC_SET( device, UniqueDevice );

     if (clazz->Initialize) {
          ret = clazz->Initialize( device, device->data, device->ctx );
          if (ret) {
               D_MAGIC_CLEAR( device );
               goto error;
          }
     }

     D_DEBUG_AT( UniQuE_Device, "  -> device created (%p)\n", device );

     *ret_device = device;

     return DFB_OK;


error:
     if (device->reactor)
          fusion_reactor_free( device->reactor );

     if (device->data)
          SHFREE( context->shmpool, device->data );

     SHFREE( context->shmpool, device );

     return ret;
}
