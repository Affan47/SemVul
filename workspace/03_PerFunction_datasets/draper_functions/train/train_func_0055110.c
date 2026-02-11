SummonedMovementInform(Creature* pSummoned, uint32 uiMotionType, uint32 uiPointId) override
    {
        if (uiMotionType != POINT_MOTION_TYPE || !uiPointId || pSummoned->GetEntry() != NPC_WINDSOR)
        {
            return;
        }


        if (uiPointId && HasEscortState(STATE_ESCORT_PAUSED))
        {
            StartNextDialogueText(NPC_WINDSOR);
        }
    }
