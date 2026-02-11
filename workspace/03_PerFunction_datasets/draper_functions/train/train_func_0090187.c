setFilename( char *fname, int kind )
{
    static int f_gram = 0;
    static int f_voca = 0;
    static int f_out = 0;
    static int f_header = 0;
    switch( kind ){
      case 1:
	strcpy( GramFile, fname );
	f_gram = 1;
	break;
      case 2:
	strcpy( VocaFile, fname );
	f_voca = 1;
	break;
      case 3:
	strcpy( FAfile, fname );
	f_out = 1;
	break;
      case 4:
	strcpy( HeaderFile, fname );
	f_header = 1;
	break;
      case 5:
	sprintf( GramFile, "%s.grammar", fname );
	sprintf( VocaFile, "%s.voca", fname );
	if( SW_NFAoutput ){
	    sprintf( FAfile, "%s.nfa", fname );
	} else {
	    sprintf( FAfile, "%s.dfa", fname );
	}
	optF = 1;
	sprintf( HeaderFile, "%s.h", fname );
	f_gram = f_voca = f_out = f_header = 1;
	return( 1 );
    }
    if( f_gram && f_voca && f_out && f_header ){
	return( 1 );
    } else {
	return( 0 );
    }
}
