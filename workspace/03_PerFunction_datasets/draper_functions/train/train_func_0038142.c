OnCreatureDeath(Creature* pCreature)
{
    if (pCreature->GetEntry() == NPC_INTERROGATOR_VISHAS)
    {

        if (Creature* pVorrel = GetSingleCreatureFromStorage(NPC_VORREL))
        {
            DoScriptText(SAY_TRIGGER_VORREL, pVorrel);
        }
    }
}
