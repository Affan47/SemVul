DoGetDetails() const
    {
        tString ret;
        if ( se_votingPrivacy <= -1 && bool( suggestor_ ) )
            ret << tOutput( "$vote_submitter_text", suggestor_->Name( user_ ) ) << " ";

        return ret;
    }
