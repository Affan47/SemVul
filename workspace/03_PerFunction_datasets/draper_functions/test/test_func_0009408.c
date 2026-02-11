OnCreatureEnterCombat(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {

        case NPC_BLACKHAND_INCARCERATOR:
            SetData(TYPE_EMBERSEER, IN_PROGRESS);
            break;
    }
}
