GetControlMessage( nMessage& m )
    {
        if ( sn_GetNetState() == nSERVER )
        {
            unsigned short id;
            m.Read( id );

            bool result;
            m >> result;
            result = result ? 1 : 0;

            for ( int i = items_.Len()-1; i>=0; --i )
            {
                eVoteItem* vote = items_[i];
                if ( vote->id_ == id )
                {

                    tCONTROLLED_PTR( eVoter ) voter = se_GetVoter( m );
                    if ( voter )
                    {

                        tOutput voteMessage;
                        voteMessage.SetTemplateParameter( 1, voter->Name( m.SenderID() ) );
                        voteMessage.SetTemplateParameter( 2, vote->GetDescription() );
                        if ( result )
                            voteMessage << "$vote_vote_for";
                        else
                            voteMessage << "$vote_vote_against";


                        if ( se_votingPrivacy <= -2 )
                            sn_ConsoleOut( voteMessage );
                        else if ( se_votingPrivacy <= 0 )
                            con << voteMessage;
                        else
                        {
                            sn_ConsoleOut( voteMessage, m.SenderID() );
                        }


                        vote->RemoveVoter( voter );


                        vote->voters_[ result ].Insert( voter );
                    }


                    vote->Evaluate();
                    return;
                }
            }
        }
    }
