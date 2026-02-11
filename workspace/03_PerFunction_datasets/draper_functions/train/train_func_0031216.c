check_remote( const Job *job ) const
{
    bool local = (job->submitter == this);
    return local || !noremote;
}
