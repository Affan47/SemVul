stret_iteration_init( StretIteration *iteration, StretRegion *region, StretRegion *abort_at )
{
     D_ASSERT( iteration != NULL );

     D_MAGIC_ASSERT( region, StretRegion );
     D_MAGIC_ASSERT_IF( abort_at, StretRegion );

     D_DEBUG_AT( UniQuE_StReT, "stret_iteration_init()\n" );

     iteration->frame = -1;
     iteration->x0    = 0;
     iteration->y0    = 0;
     iteration->abort = abort_at;

     do {
          int last_level = region->levels - 1;
          int last_child = fusion_vector_size( &region->children[last_level] ) - 1;

          iteration->frame++;

          iteration->x0 += region->bounds.x1;
          iteration->y0 += region->bounds.y1;

          iteration->stack[iteration->frame].region = region;
          iteration->stack[iteration->frame].level  = last_level;
          iteration->stack[iteration->frame].index  = last_child - 1;

          D_DEBUG_AT( UniQuE_StReT, "  -> (%d) %p, last level %d, last index %d\n",
                      iteration->frame, region, last_level, last_child );

          if (last_child >= 0) {
               region = fusion_vector_at( &region->children[last_level], last_child );

               D_MAGIC_ASSERT( region, StretRegion );
          }
     } while (fusion_vector_size( &region->children[region->levels - 1] ) && check_depth( iteration->frame + 1 ));

     iteration->stack[iteration->frame].index++;

     D_MAGIC_SET( iteration, StretIteration );
}
