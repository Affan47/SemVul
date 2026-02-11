RemoveSubStr( int start, int length ) {
    int strLen = Len()-1;
    if ( length < 0 ) {
        start += length;
        length = abs( length );
    }

    if ( start + length > strLen || start < 0 || length == 0 ) {
        return;
    }

    if ( start == 0 ) {
        if ( strLen - length == 0 ) {
            *this = ("");
        }
        else {
            *this = SubStr( start + length, strLen );
        }
    }
    else {
        *this = SubStr( 0, start ) << SubStr( start + length, strLen );
    }

    SetLen(strLen+1-length);
}
