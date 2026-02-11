draw_pt_split_prim(unsigned prim, unsigned *first, unsigned *incr)
{
   switch (prim) {
   case PIPE_PRIM_POINTS:
      *first = 1;
      *incr = 1;
      break;
   case PIPE_PRIM_LINES:
      *first = 2;
      *incr = 2;
      break;
   case PIPE_PRIM_LINE_STRIP:
   case PIPE_PRIM_LINE_LOOP:
      *first = 2;
      *incr = 1;
      break;
   case PIPE_PRIM_LINES_ADJACENCY:
      *first = 4;
      *incr = 4;
      break;
   case PIPE_PRIM_LINE_STRIP_ADJACENCY:
      *first = 4;
      *incr = 1;
      break;
   case PIPE_PRIM_TRIANGLES:
      *first = 3;
      *incr = 3;
      break;
   case PIPE_PRIM_TRIANGLES_ADJACENCY:
      *first = 6;
      *incr = 6;
      break;
   case PIPE_PRIM_TRIANGLE_STRIP:
   case PIPE_PRIM_TRIANGLE_FAN:
   case PIPE_PRIM_POLYGON:
      *first = 3;
      *incr = 1;
      break;
   case PIPE_PRIM_TRIANGLE_STRIP_ADJACENCY:
      *first = 6;
      *incr = 2;
      break;
   case PIPE_PRIM_QUADS:
      *first = 4;
      *incr = 4;
      break;
   case PIPE_PRIM_QUAD_STRIP:
      *first = 4;
      *incr = 2;
      break;
   default:
      assert(0);
      *first = 0;
      *incr = 1;
      break;
   }
}
