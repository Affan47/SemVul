addConstraintToIndex( const QModelIndex& idx, const Constraint& c )
{
    IndexType::iterator it = indexMap.find(idx);
    while (it != indexMap.end() && it.key() == idx) {

        if ( *it == c ) return;
        ++it;
    }

    indexMap.insert( idx, c );
}
