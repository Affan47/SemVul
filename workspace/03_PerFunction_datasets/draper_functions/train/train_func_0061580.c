dump_srcreg( struct sh_srcreg srcreg, struct sh_srcreg *indreg, const struct dump_info *di )
{
   switch (srcreg.modifier) {
   case SVGA3DSRCMOD_NEG:
   case SVGA3DSRCMOD_BIASNEG:
   case SVGA3DSRCMOD_SIGNNEG:
   case SVGA3DSRCMOD_X2NEG:
   case SVGA3DSRCMOD_ABSNEG:
      _debug_printf( "-" );
      break;
   case SVGA3DSRCMOD_COMP:
      _debug_printf( "1-" );
      break;
   case SVGA3DSRCMOD_NOT:
      _debug_printf( "!" );
   }
   dump_reg( *(struct sh_reg *) &srcreg, indreg, di );
   switch (srcreg.modifier) {
   case SVGA3DSRCMOD_NONE:
   case SVGA3DSRCMOD_NEG:
   case SVGA3DSRCMOD_COMP:
   case SVGA3DSRCMOD_NOT:
      break;
   case SVGA3DSRCMOD_BIAS:
   case SVGA3DSRCMOD_BIASNEG:
      _debug_printf( "_bias" );
      break;
   case SVGA3DSRCMOD_SIGN:
   case SVGA3DSRCMOD_SIGNNEG:
      _debug_printf( "_bx2" );
      break;
   case SVGA3DSRCMOD_X2:
   case SVGA3DSRCMOD_X2NEG:
      _debug_printf( "_x2" );
      break;
   case SVGA3DSRCMOD_DZ:
      _debug_printf( "_dz" );
      break;
   case SVGA3DSRCMOD_DW:
      _debug_printf( "_dw" );
      break;
   case SVGA3DSRCMOD_ABS:
   case SVGA3DSRCMOD_ABSNEG:
      _debug_printf("_abs");
      break;
   default:
      assert( 0 );
   }
   if (srcreg.swizzle_x != 0 || srcreg.swizzle_y != 1 || srcreg.swizzle_z != 2 || srcreg.swizzle_w != 3) {
      _debug_printf( "." );
      if (srcreg.swizzle_x == srcreg.swizzle_y && srcreg.swizzle_y == srcreg.swizzle_z && srcreg.swizzle_z == srcreg.swizzle_w) {
         _debug_printf( "%c", "xyzw"[srcreg.swizzle_x] );
      }
      else {
         _debug_printf( "%c", "xyzw"[srcreg.swizzle_x] );
         _debug_printf( "%c", "xyzw"[srcreg.swizzle_y] );
         _debug_printf( "%c", "xyzw"[srcreg.swizzle_z] );
         _debug_printf( "%c", "xyzw"[srcreg.swizzle_w] );
      }
   }
}
