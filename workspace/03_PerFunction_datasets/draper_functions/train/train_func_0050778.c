stret_region_get_size( StretRegion  *region,
                       DFBDimension *ret_size )
{
     D_MAGIC_ASSERT( region, StretRegion );

     D_ASSERT( ret_size != NULL );

     ret_size->w = region->bounds.x2 - region->bounds.x1 + 1;
     ret_size->h = region->bounds.y2 - region->bounds.y1 + 1;
}
