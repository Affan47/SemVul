addConstraint( const Constraint& c )
{

    bool hasConstraint = d->constraints.contains( c );


    if ( !hasConstraint ) {
        d->constraints.push_back( c );
        d->addConstraintToIndex( c.startIndex(), c );
        d->addConstraintToIndex( c.endIndex(), c );
        emit constraintAdded( c );
    }
}
