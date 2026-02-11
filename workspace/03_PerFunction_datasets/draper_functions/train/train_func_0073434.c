DoRemovePlayerFromStomach(Player* pPlayer)
    {
        if (pPlayer)
        {
            m_lPlayersInStomachList.remove(pPlayer->GetObjectGuid());
        }
    }
