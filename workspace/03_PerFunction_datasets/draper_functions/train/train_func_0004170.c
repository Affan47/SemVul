AIM_Initialize()
{

    if (m_AI_locked)
    {
        DEBUG_FILTER_LOG(LOG_FILTER_AI_AND_MOVEGENSS, "AIM_Initialize: failed to init, locked.");
        return false;
    }

    CreatureAI* oldAI = i_AI;
    i_motionMaster.Initialize();
    i_AI = FactorySelector::selectAI(this);
    delete oldAI;
    return true;
}
