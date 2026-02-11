SummonedMovementInform(Creature* pSummoned, uint32 uiMoveType, uint32 uiPointId) override
    {
        if (uiMoveType != POINT_MOTION_TYPE || !uiPointId || pSummoned->GetEntry() != NPC_BIG_WILL)
        {
            return;
        }

        pSummoned->setFaction(FACTION_HOSTILE_WILL);

        if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_playerGuid))
        {
            DoScriptText(SAY_BIG_WILL_READY, pSummoned, pPlayer);
            pSummoned->SetFacingToObject(pPlayer);
        }
    }
