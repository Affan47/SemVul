makeChain (void)
{

    for ( int16_t row = 0 ; row < k_GridHeight ; ++row )
    {
        for ( int16_t column = 0 ; column < k_GridWidth ; ++column )
        {
            std::set<std::pair<int16_t, int16_t> > visitedPositions;
            std::vector<FallingAmoeba> group;
            std::vector<FallingAmoeba> ghosts;
            makeGroup (group, ghosts, column, row, visitedPositions);
            if ( 4 <= group.size () )
            {
                int16_t meanXPosition = 0;
                int16_t meanYPosition = 0;

                m_DyingTime = k_DefaultDyingTime;
                m_BlinkTime = k_DefaultBlinkTime;
                for (std::vector<FallingAmoeba>::iterator currentAmoeba =
                        group.begin () ;
                     currentAmoeba != group.end () ; ++currentAmoeba )
                {
                    meanXPosition += currentAmoeba->x;
                    meanYPosition += currentAmoeba->y;
                    currentAmoeba->amoeba->setDying (true);
                    m_DyingAmoebas.push_back (*currentAmoeba);
                }

                for (std::vector<FallingAmoeba>::iterator currentGhost =
                        ghosts.begin () ;
                     currentGhost != ghosts.end () ; ++currentGhost )
                {
                    currentGhost->amoeba->setDying (true);
                    m_DyingAmoebas.push_back (*currentGhost);
                }

                meanXPosition /= group.size ();
                meanYPosition /= group.size ();
                addChainLabel (getCurrentStepChain () + 1,
                               getGridPositionX () +
                               meanXPosition * getAmoebaSize () +
                               getAmoebaSize () / 2,
                               getGridPositionY () +
                               (meanYPosition - k_FirstVisibleHeight) *
                               getAmoebaSize () + getAmoebaSize () / 2);
            }
        }
    }

    findFloatingAmoebas ();

    if ( m_FloatingAmoebas.empty () && m_DyingAmoebas.empty () )
    {
        if ( getNumberOfWaitingGhosts () == 0 )
        {


                if ( 0 != getAmoebaAt (3, k_FirstVisibleHeight - 1) )
                {
                    markAsFilled ();
                }
                else
                {
                    scheduleFallingPair ();
                }
        }
        else
        {
            makeGhostsFall ();
        }
    }
}
