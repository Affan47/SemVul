HandleNpcSetPhaseCommand(char* args)
{
    if (!*args)
        return false;

    uint32 phasemask = (uint32) atoi(args);
    if (phasemask == 0)
    {
        SendSysMessage(LANG_BAD_VALUE);
        SetSentErrorMessage(true);
        return false;
    }

    Creature* pCreature = getSelectedCreature();
    if (!pCreature)
    {
        SendSysMessage(LANG_SELECT_CREATURE);
        SetSentErrorMessage(true);
        return false;
    }

    pCreature->SetPhaseMask(phasemask, true);

    if (pCreature->HasStaticDBSpawnData())
        pCreature->SaveToDB();

    return true;
}
