LogScoreDifferences( void )
{
    for ( int i = teams.Len()-1; i>=0; --i )
    {
        eTeam* t = teams(i);
        t->LogScoreDifference();
    }
}
