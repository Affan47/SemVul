select_population( APG::ConstraintSolver::Population& population, Meta::TrackList* best )
{
    Population::Iterator it = population.begin();
    while ( it != population.end() ) {
        if ( it.key() == best ) {
            ++it;
            if ( it == population.end() )
                break;
        }

        if ( select( it.value() ) ) {
            ++it;
        } else {
            delete it.key();
            it = population.erase( it );
        }
    }
}
