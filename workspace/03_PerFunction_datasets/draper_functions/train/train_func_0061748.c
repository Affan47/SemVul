getSolverHints()
{
    QList<MoveHint> hintList;

    if ( m_solverThread && m_solverThread->isRunning() )
        m_solverThread->abort();

    solver()->translate_layout();
    bool debug = false;
#if DEBUG_HINTS
    debug = true;
#endif
    solver()->patsolve( 1, debug );

    foreach ( const MOVE & m, solver()->firstMoves )
    {
        MoveHint mh = solver()->translateMove( m );
	hintList << mh;
    }
    return hintList;
}
