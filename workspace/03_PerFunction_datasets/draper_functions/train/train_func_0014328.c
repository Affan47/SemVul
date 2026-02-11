PosWordLeft( int start ) {
    return -1 * Reverse().PosWordRight( Len() - start - 1 );
}
