AddSC_darkshore()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_kerlonian";
    pNewScript->GetAI = &GetAI_npc_kerlonian;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_kerlonian;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_prospector_remtravel";
    pNewScript->GetAI = &GetAI_npc_prospector_remtravel;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_prospector_remtravel;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_threshwackonator";
    pNewScript->GetAI = &GetAI_npc_threshwackonator;
    pNewScript->pGossipHello = &GossipHello_npc_threshwackonator;
    pNewScript->pGossipSelect = &GossipSelect_npc_threshwackonator;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_volcor";
    pNewScript->GetAI = &GetAI_npc_volcor;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_volcor;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_therylune";
    pNewScript->GetAI = &GetAI_npc_therylune;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_therylune;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_rabid_bear";
    pNewScript->GetAI = &GetAI_npc_rabid_bear;
    pNewScript->RegisterSelf();
}
