dump_sampleinfo(struct sh_sampleinfo sampleinfo)
{
   assert( sampleinfo.is_reg == 1 );

   switch (sampleinfo.texture_type) {
   case SVGA3DSAMP_2D:
      _debug_printf( "_2d" );
      break;
   case SVGA3DSAMP_CUBE:
      _debug_printf( "_cube" );
      break;
   case SVGA3DSAMP_VOLUME:
      _debug_printf( "_volume" );
      break;
   default:
      assert( 0 );
   }
}
