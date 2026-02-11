MoveInLineOfSight(Unit* pWho) override
    {

        if (m_uiQuestId == QUEST_ESCAPE_THROUGH_STEALTH)
        {
            return;
        }

        npc_escortAI::MoveInLineOfSight(pWho);
    }
