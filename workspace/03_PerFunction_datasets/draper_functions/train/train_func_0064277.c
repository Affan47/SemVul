OnPlayerEnter(Player* pPlayer)
{

    if (GetData(TYPE_SAPPHIRON) != SPECIAL)
    {
        return;
    }


    if (GetSingleCreatureFromStorage(NPC_SAPPHIRON, true))
    {
        return;
    }

    pPlayer->SummonCreature(NPC_SAPPHIRON, aSapphPositions[0], aSapphPositions[1], aSapphPositions[2], aSapphPositions[3], TEMPSUMMON_DEAD_DESPAWN, 0);
}
