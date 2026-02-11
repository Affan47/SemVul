Reverse() {
    tString reversed;
    for ( int index = Len() - 2; index >= 0; index-- ) {
        reversed << ( *this ) ( index );
    }

    return reversed;
}
