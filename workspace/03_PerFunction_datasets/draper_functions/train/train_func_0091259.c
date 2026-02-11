FirstType() const
{
    for ( int i = 0; i < nBandwidthTask::Type_Count; ++i )
    {
        nType type = nType(i);
        if ( this->Tasks(type).Len() > 0 )
        {
            return type;
        }
    }

    return nBandwidthTask::Type_Count;
}
