unique_device_filter ( UniqueDeviceClassID     class_id,
                       const UniqueInputEvent *event,
                       const UniqueInputEvent *filter )
{
     const UniqueDeviceClass *clazz;

     D_ASSERT( class_id >= 0 );
     D_ASSERT( class_id < MAX_CLASSES );

     D_ASSERT( event != NULL );
     D_ASSERT( filter != NULL );

     clazz = classes[class_id];

     D_ASSERT( clazz != NULL );

     if (clazz->FilterEvent)
          return clazz->FilterEvent( event, filter );

     return false;
}
