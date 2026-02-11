setGameState( const QString & state )
{
    Q_UNUSED( state );

    emit newCardsPossible( !talon->isEmpty() || pile->count() > 1 );
}
