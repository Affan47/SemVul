save_centers(CENTER_ORDER * pcent, int fpos, int npos, const char * arm )
{
  static FILE * fgnu = NULL, * freg = NULL ;
  static const char * gnuname =NULL ;
  int first_call =0;
  FILE *fout ;
  char fname[32] ;
  int i=0, order=0 ;
  CENTER_ORDER * ppcent=NULL ;

  if ( fgnu == NULL ) {
    gnuname = xsh_stringcat_any( "all_orders_", arm, ".gnu", NULL ) ;
    fgnu = fopen( gnuname, "w" ) ;
    fprintf( fgnu, "set term x11\nplot " ) ;
    first_call = 1 ;
  }
  else first_call = 0 ;
  ppcent = pcent + fpos ;
  order = ppcent->order ;
  sprintf( fname, "order_%s_%02d.dat", arm, order ) ;
  fout = fopen( fname, "w" ) ;

  if ( !first_call ) fprintf( fgnu, "," ) ;
  fprintf( fgnu, "'%s' u 1:2 w points pt 5 t''", fname ) ;

  for( i = fpos ; i<npos; i++, ppcent++ )
    fprintf( fout, "%d %d %.3lf\n",
	     ppcent->pos_x, ppcent->pos_y, ppcent->flux ) ;

  fclose( fout ) ;
  if ( order == 0 ) {
    fprintf( fgnu, "\n" ) ;
    fclose( fgnu ) ;
  }


  if ( freg == NULL ) {
    freg = fopen( "order_create.reg", "w" ) ;
  }
  fprintf( freg, "# Region file format: DS9 version 4.0\n" ) ;
  fprintf( freg, "global color=red font=\"helvetica 4 normal\"select=1 highlite=1 edit=1 move=1 delete=1 include=1 fixed=0 source\n" ) ;
  fprintf( freg, "image\n# RED center_x center_y (pixels)\n" ) ;
  for( ppcent = pcent+fpos, i = fpos ; i <npos ; i++, ppcent++ ) {
    fprintf( freg, "point(%d.,%d.) #point=cross color=red font=\"helvetica 4 normal\"\n", ppcent->pos_x, ppcent->pos_y ) ;
  }
  if ( order == 0 ) {
    fclose( freg ) ;
  }
}
