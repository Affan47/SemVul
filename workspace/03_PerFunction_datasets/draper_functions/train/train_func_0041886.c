ReceiveAIEvent(AIEventType eventType, Creature* , Unit* pInvoker, uint32 uiMiscValue) override
    {
        if (eventType == AI_EVENT_START_ESCORT && pInvoker->GetTypeId() == TYPEID_PLAYER)
        {

            m_creature->SetStandState(UNIT_STAND_STATE_STAND);
            m_creature->SetFactionTemporary(FACTION_ESCORT_A_NEUTRAL_PASSIVE, TEMPFACTION_RESTORE_RESPAWN);
            Start(false, (Player*)pInvoker, GetQuestTemplateStore(uiMiscValue), true);
        }
    }
