readline ( IFILE *f, short *runs, int *pels )
{
  int nr = 0, nb ;
  uchar bits [ MAXBITS ] ;

  if ( f->lines != 0 ) {
    switch ( f->page->format ) {

    case P_TEXT :
      if ( f->txtlines <= 0 ) {
	if ( fgets ( f->text, MAXLINELEN, f->f ) ) {
	  f->txtlines = f->charh ;
	  if ( strchr ( f->text, FF ) ) {
	    f->lines = 0 ;
	    nr = EOF ;
	  }
	} else {
	  nr = EOF ;
	}
      }
      if ( nr != EOF ) {
	nr = texttorun ( (uchar*) f->text, f->font, f->charh - f->txtlines,
			f->charw, f->charh, f->lmargin,
			runs, pels ) ;
	f->txtlines-- ;
      }
      break ;

    case P_RAW:
    case P_PBM:
      if ( fread ( bits, 1, f->page->w/8, f->f ) != f->page->w/8 ) {
	nr = EOF ;
      } else {
	nr = bittorun ( bits, f->page->w/8, runs ) ;
	if ( pels ) *pels = f->page->w ;
      }
      break ;

    case P_FAX:
      nr = readruns ( f, runs, pels ) ;
      break ;

    case P_PCX:
      nb = ( ( f->page->w + 15 ) / 16 ) * 2 ;
      if ( readpcx ( (char*) bits, nb, f ) != 0 ) {
	nr = EOF ;
      } else {
   	nr = bittorun ( bits, nb, runs ) ;
	if ( pels ) *pels = f->page->w ;
      }
      break ;

    }
  } else {
    nr = EOF ;
  }

  if ( nr >= 0 && f->page->black_is_zero ) {
    nr = xinvert ( runs, nr ) ;
  }

  if ( nr >= 0 && f->lines > 0 ) f->lines-- ;

  return nr ;
}
