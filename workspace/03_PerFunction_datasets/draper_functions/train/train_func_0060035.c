unregister_region_classes( WMShared *shared )
{
     int i;

     D_MAGIC_ASSERT( shared, WMShared );

     for (i=_URCI_NUM-1; i>=0; i--)
          stret_class_unregister( shared->region_classes[i] );

     return DFB_OK;
}
