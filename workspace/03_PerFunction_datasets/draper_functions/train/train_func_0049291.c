run()
{
    if ( !m_readyToRun ) {
        error() << "DANGER WILL ROBINSON!  A ConstraintSolver (serial no:" << m_serialNumber << ") tried to run before its QueryMaker finished!";
        m_abortRequested = true;
        return;
    }

    if ( m_domain.empty() ) {
        debug() << "The QueryMaker returned no tracks";
        return;
    } else {
        debug() << "Domain has" << m_domain.size() << "tracks";
    }

    debug() << "Running ConstraintSolver" << m_serialNumber;

    emit totalSteps( m_maxGenerations );


    Population population;
    quint32 generation = 0;
    Meta::TrackList* best = NULL;
    while ( !m_abortRequested && ( generation < m_maxGenerations ) ) {
        m_suggestedPlaylistSize = m_constraintTreeRoot->suggestPlaylistSize();
        fill_population( population );
        best = find_best( population );
        if ( population.value( best ) < m_satisfactionThreshold ) {
            select_population( population, best );
            mutate_population( population );
            generation++;
            emit incrementProgress();
        } else {
            break;
        }
    }
    debug() << "solution at" << (void*)(best);

    m_solvedPlaylist = best->mid( 0 );
    m_finalSatisfaction = m_constraintTreeRoot->satisfaction( m_solvedPlaylist );


    Population::iterator it = population.begin();
    while ( it != population.end() ) {
        delete it.key();
        it = population.erase( it );
    }

    emit endProgressOperation( this );
}
