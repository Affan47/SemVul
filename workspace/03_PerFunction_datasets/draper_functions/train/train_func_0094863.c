LogScoreDifference( void )
{
    if ( lastScore_ > IMPOSSIBLY_LOW_SCORE && IsHuman() )
    {
        int scoreDifference = score - lastScore_;
        lastScore_ = IMPOSSIBLY_LOW_SCORE;
        se_roundScoreWriter << scoreDifference << GetUserName();
        if ( currentTeam )
            se_roundScoreWriter << FilterName( currentTeam->Name() );
        se_roundScoreWriter.write();
    }
}
