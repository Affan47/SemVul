Convexity( void )
{
   register tFace    f;
   register tVertex  v;
   int               vol;

   f = faces;

   do {
      v = vertices;
      do {
	 if ( v->mark ) {
	    vol = VolumeSign( f, v );
	    if ( vol < 0 )
	       break;
	 }
	 v = v->next;
      } while ( v != vertices );

      f = f->next;

   } while ( f != faces );

   if ( f != faces )
      std::cerr << "Checks: NOT convex.\n" ;
   else if ( check )
      std::cerr << "Checks: convex.\n" ;
}
