UpdateShuffleSpamTesters()
{
    for ( int i = se_PlayerNetIDs.Len()-1; i>=0; --i )
    {
        ePlayerNetID *p = se_PlayerNetIDs( i );
        p->shuffleSpam.Reset();
    }
}
