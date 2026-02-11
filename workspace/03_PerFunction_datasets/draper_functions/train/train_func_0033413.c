StartSummonEvent(Player* pPlayer)
    {
        m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);


        if (m_creature->GetMap()->GetCreature(m_ragnarosGuid))
        {
            return;
        }

        DoScriptText(SAY_SUMMON_0, m_creature, pPlayer);

        m_uiSpeechTimer = 5000;
        m_uiSpeech = 10;
    }
