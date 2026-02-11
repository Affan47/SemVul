SetChallengerReady(Creature* pChallenger)
    {
        pChallenger->setFaction(FACTION_HOSTILE_CHALLENGER);
        pChallenger->HandleEmote(EMOTE_ONESHOT_ROAR);
        ++m_uiChallengerCount;

        if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_playerGuid))
        {
            pChallenger->AI()->AttackStart(pPlayer);
        }
    }
