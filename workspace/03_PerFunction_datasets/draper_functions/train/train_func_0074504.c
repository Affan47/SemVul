finishedFunctorEndOfRage( PT_DocPosition ,
                                      PT_DocPosition rangeEndPos,
                                      PT_DocPosition curPos,
                                      PL_Listener*  )
{
    if( curPos >= rangeEndPos )
        return true;
    return false;
}
