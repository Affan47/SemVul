convert_block_to_byte( void *in, unsigned char *out, int npts,
                           int in_type, double *dispmin, double *dispmax )
{
   if( (lastLookupMin==0.0 && lastLookupMax==0.0)
       || (*dispmin==0.0 && *dispmax==0.0) ) {
      return convert_block( in, npts, in_type, dispmin, dispmax, out, NULL );
   } else {
      return convert_block( in, npts, in_type,
                            &lastLookupMin, &lastLookupMax, out, NULL );
   }
}
