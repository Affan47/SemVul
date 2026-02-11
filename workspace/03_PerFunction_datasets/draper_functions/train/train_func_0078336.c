SendTalking(uint32 textID)
{
    GossipText const* pGossip = sObjectMgr.GetGossipText(textID);

    WorldPacket data(SMSG_NPC_TEXT_UPDATE, 100);
    data << textID;

    if (!pGossip)
    {
        for (uint32 i = 0; i < 8; ++i)
        {
            data << float(0);
            data << "Greetings $N";
            data << "Greetings $N";
            data << uint32(0);
            data << uint32(0);
            data << uint32(0);
            data << uint32(0);
            data << uint32(0);
            data << uint32(0);
            data << uint32(0);
        }
    }
    else
    {
        std::string Text_0[MAX_GOSSIP_TEXT_OPTIONS], Text_1[MAX_GOSSIP_TEXT_OPTIONS];
        for (int i = 0; i < MAX_GOSSIP_TEXT_OPTIONS; ++i)
        {
            Text_0[i] = pGossip->Options[i].Text_0;
            Text_1[i] = pGossip->Options[i].Text_1;
        }

        int loc_idx = GetMenuSession()->GetSessionDbLocaleIndex();

        sObjectMgr.GetNpcTextLocaleStringsAll(textID, loc_idx, &Text_0, &Text_1);

        for (int i = 0; i < MAX_GOSSIP_TEXT_OPTIONS; ++i)
        {
            data << pGossip->Options[i].Probability;

            if (Text_0[i].empty())
                { data << Text_1[i]; }
            else
                { data << Text_0[i]; }

            if (Text_1[i].empty())
                { data << Text_0[i]; }
            else
                { data << Text_1[i]; }

            data << pGossip->Options[i].Language;

            for (int j = 0; j < 3; ++j)
            {
                data << pGossip->Options[i].Emotes[j]._Delay;
                data << pGossip->Options[i].Emotes[j]._Emote;
            }
        }
    }
    GetMenuSession()->SendPacket(&data);

    DEBUG_LOG("WORLD: Sent SMSG_NPC_TEXT_UPDATE ");
}
