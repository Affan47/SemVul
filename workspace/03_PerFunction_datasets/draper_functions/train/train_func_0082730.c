stret_class_register( const StretRegionClass *clazz,
                      StretRegionClassID     *ret_id )
{
     int i;

     D_DEBUG_AT( UniQuE_StReT, "stret_class_register( %p )\n", clazz );

     D_ASSERT( clazz != NULL );
     D_ASSERT( ret_id != NULL );

     pthread_mutex_lock( &classes_lock );

     if (classes_count == MAX_CLASSES) {
          D_WARN( "too many classes" );
          pthread_mutex_unlock( &classes_lock );
          return DFB_LIMITEXCEEDED;
     }

     classes_count++;

     for (i=0; i<MAX_CLASSES; i++) {
          if (!classes[i]) {
               classes[i] = clazz;
               break;
          }
     }

     D_DEBUG_AT( UniQuE_StReT, "    -> New class ID is %d.\n", i );

     D_ASSERT( i < MAX_CLASSES );

     *ret_id = i;

     pthread_mutex_unlock( &classes_lock );

     return DFB_OK;
}
