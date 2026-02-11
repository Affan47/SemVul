update (uint32_t elapsedTime)
{
    if ( allCharactersSelected () )
    {
        setTimeToWait (getTimeToWait () - elapsedTime);
        if ( getTimeToWait () <= 0 )
        {
            std::vector <TournamentState::Player> tournamentPlayers;
            for (std::vector <SelectedCharacter>::const_iterator currentPlayer = m_SelectedCharacters.begin() ;
                 currentPlayer != m_SelectedCharacters.end() ; ++currentPlayer)
            {
                TournamentState::Player player;
                player.characterIndex = currentPlayer->index;
                player.name = m_Characters[currentPlayer->index].name;
                player.isComputerPlayer = k_ComputerFacesRow == currentPlayer->row;
                player.computerPlayerLevel = currentPlayer->col;
                tournamentPlayers.push_back (player);
            }
            System::getInstance ().removeActiveState (false);
            System::getInstance ().setActiveState (
                    new TournamentState (tournamentPlayers));
        }
    }

}
