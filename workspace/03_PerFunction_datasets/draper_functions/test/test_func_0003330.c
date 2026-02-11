HandleObjectiveComplete(uint32 eventId, std::list<Player*> players, Team team)
{
    if (eventId == EVENT_HALAA_BANNER_WIN_ALLIANCE || eventId == EVENT_HALAA_BANNER_WIN_HORDE)
    {
        for (std::list<Player*>::iterator itr = players.begin(); itr != players.end(); ++itr)
        {
            if ((*itr) && (*itr)->GetTeam() == team)
                (*itr)->KilledMonsterCredit(NPC_HALAA_COMBATANT);
        }
    }
}
