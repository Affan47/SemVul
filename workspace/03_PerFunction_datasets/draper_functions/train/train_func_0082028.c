getClass( char *name )
{
    CLASS *class = ClassList;
    if( class == NULL ) return( NULL );
    while( 1 ){
	if( strcmp( class->name, name ) == 0 ){
	  class->used = 1;
	    return( class );
	}
	class = class->next;
	if( class == NULL ) return( NULL );
    }
}
