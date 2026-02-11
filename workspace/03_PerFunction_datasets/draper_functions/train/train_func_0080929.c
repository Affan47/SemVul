UnSummon()
{
    CombatStop();

    if (GetSummonerGuid().IsCreature())
        if (Creature* sum = GetMap()->GetCreature(GetSummonerGuid()))
            if (sum->AI())
                { sum->AI()->SummonedCreatureDespawn(this); }

    AddObjectToRemoveList();
}
