DXDeleteHashElement( HashTable hashTable, Key key )
{
    HashElement elt;

    if ( NULL != ( elt = _QueryHashElement( hashTable, key ) ) )
        elt->u.pseudoKey = 0;

    return OK;
}
