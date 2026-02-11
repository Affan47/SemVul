addGhostAmoebas (void)
{
    const Level &currentLevel = k_Levels[getCurrentLevel () - 1];
    if ( currentLevel.maxAmoebas != 0 &&
         (rand () % 101) < currentLevel.probabilityToAdd )
    {
        getPlayerGrid ()->incrementNumberOfWaitingGhosts ((rand () %
                                                 currentLevel.maxAmoebas) + 1);
    }
}
