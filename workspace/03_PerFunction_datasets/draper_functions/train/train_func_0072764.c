stret_region_at( StretRegion        *region,
                 int                 x,
                 int                 y,
                 StretRegionFlags    flags,
                 StretRegionClassID  class_id )
{
     StretIteration iteration;
     DFBRegion      area = { x, y, x, y };

     D_MAGIC_ASSERT( region, StretRegion );

     D_DEBUG_AT( UniQuE_StReT, "stret_region_at( %p, %d, %d, 0x%08x )\n", region, x, y, flags );

     if (! D_FLAGS_IS_SET( region->flags, SRF_ACTIVE )) {
          D_DEBUG_AT( UniQuE_StReT, "  -> Region is not active.\n" );
          return NULL;
     }


     stret_iteration_init( &iteration, region, NULL );

     while ((region = stret_iteration_next( &iteration, &area )) != NULL) {
          if (! D_FLAGS_ARE_SET( region->flags, flags ))
               continue;

          if (class_id != SRCID_UNKNOWN && region->clazz != class_id)
               continue;

          return region;
     }

     return NULL;
}
