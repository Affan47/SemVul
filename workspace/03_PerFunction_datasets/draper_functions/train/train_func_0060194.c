entryNonTerm( char *name, BODY *body, int modeAccpt, int start, int member, int tmp )
{
    CLASS *class;

    class = getClass( name );
    if( class != NULL ){
	if( member ){
	    errMes("Accepted flag of class \"%s\" is re-assigned", HeadName );
	    ErrParse++;
	}
    } else {
	if( (class = malloc( sizeof(CLASS) )) == NULL ){
	    errMes( "Can't alloc memory for Class Finite Automaton." );
	}
	strcpy( class->name, name );
	if( modeAccpt ){
	    if( member ){
		class->no = CurClassNo;
	    } else {
		if( !tmp ){
		    outputHeader( name );
		    class->no = CurClassNo;
		}
	    }
	} else {
	    class->no = -1;
	}
	class->branch = 0;
	class->usedFA = 0;
	class->used = 1;
	class->bodyList = NULL;
	class->tmp = tmp;
	class->next = NULL;
	if( ClassListTail == NULL ){
	    ClassList = class;
	} else {
	    ClassListTail->next = class;
	}
	ClassListTail = class;
    }
    if( body != NULL ) pushBody( class, body );
    if( start ){
	StartFlag = 0;
	if( StartSymbol == NULL ){
	    StartSymbol = class;
	} else {
	    errMes("Start symbol is redifined as \"%s\"", class->name );
	    ErrParse++;
	}
    }
    return( class );
}
