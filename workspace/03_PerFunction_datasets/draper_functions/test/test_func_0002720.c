BalanceWithAIs(bool balanceWithAIs)
{

    EnforceConstraints();

    int numTeams = 0, numTeamsWithPlayers = 0;


    int i;
    int maxP = eTeam::minPlayers;
    for ( i = teams.Len()-1; i>=0; --i )
    {
        eTeam *t = teams(i);

        t->UpdateProperties();

        if ( t->BalanceThisTeam() )
            numTeams++;

        if ( t->NumHumanPlayers() > 0 )
            numTeamsWithPlayers++;

        int humans = t->NumHumanPlayers();

        if ( humans > maxP )
        {
            maxP = humans;
        }
    }


    for ( i = teams.Len()-1; i>=0; --i )
    {
        eTeam *t = teams(i);

        if ( t->BalanceThisTeam() )
        {
            int wishAIs = maxP - t->NumHumanPlayers();


            if ( !balanceWithAIs && t->NumHumanPlayers() > 0 )
                wishAIs = 0;


            if ( numTeamsWithPlayers >= minTeams && t->NumHumanPlayers() == 0 )
                wishAIs = 0;


            if ( wishAIs > 0 && t->NumHumanPlayers() == 0 )
                numTeamsWithPlayers++;

            int AIs = t->NumAIPlayers();

            while ( AIs > wishAIs )
            {
                int j;
                gAIPlayer* throwOut = NULL;
                for ( j=t->NumPlayers()-1; j>=0; --j )
                {
                    gAIPlayer* player = dynamic_cast<gAIPlayer*>( t->Player( j ) );
                    if ( player && !player->IsHuman() && ( !throwOut || !throwOut->Character() || !player->Character() || throwOut->Character()->iq > player->Character()->iq ) )
                    {
                        throwOut = player;
                    }
                }

                if ( throwOut )
                {
                    throwOut->RemoveFromGame();


#ifdef DEBUG
                    if ( throwOut->GetRefcount() > 1 )
                    {
                        st_Breakpoint();
                    }
#endif

                    sg_AIReferences.Remove( throwOut );
                }

                --AIs;
            }

            while ( AIs < wishAIs )
            {

                gAICharacter* best = BestIQ( 1000 );

                if ( best )
                {
                    gAIPlayer *ai 	= tNEW( gAIPlayer ) ();
                    ai->character	= best;
                    ai->SetName( best->name );
                    ai->SetTeam( t );
                    ai->UpdateTeam();

                    sg_AIReferences.Add( ai );
                }

                ++AIs;
            }
        }
    }


    nNetObject::ClearAllDeleted();
}
