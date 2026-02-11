EscapeSpecialChars( GooString* s )
{
    GooString* tmp = NULL;
    for( int i = 0, j = 0; i < s->getLength(); i++, j++ ){
        const char *replace = NULL;
        switch ( s->getChar(i) ){
	        case '"': replace = "&quot;";  break;
	        case '&': replace = "&amp;";  break;
	        case '<': replace = "&lt;";  break;
	        case '>': replace = "&gt;";  break;
	        default: continue;
	    }
	    if( replace ){
	        if( !tmp ) tmp = new GooString( s );
	        if( tmp ){
	            tmp->del( j, 1 );
	            int l = strlen( replace );
	            tmp->insert( j, replace, l );
	            j += l - 1;
	        }
	    }
	}
	return tmp ? tmp : s;
}
