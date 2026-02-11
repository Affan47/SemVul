ThisWallsLength() const
{

    REAL len = sg_CycleWallLengthFromDist( distance );
    if ( len <= 0 )
    {
        return len;
    }


    return len - GetRubber() * sg_cycleRubberWallShrink;
}
