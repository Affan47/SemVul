AddSC_boss_thekal()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_thekal";
    pNewScript->GetAI = &GetAI_boss_thekal;
    pNewScript->pEffectDummyNPC = &EffectDummyCreature_thekal_resurrection;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_zealot_lorkhan";
    pNewScript->GetAI = &GetAI_mob_zealot_lorkhan;
    pNewScript->pEffectDummyNPC = &EffectDummyCreature_thekal_resurrection;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_zealot_zath";
    pNewScript->GetAI = &GetAI_mob_zealot_zath;
    pNewScript->pEffectDummyNPC = &EffectDummyCreature_thekal_resurrection;
    pNewScript->RegisterSelf();
}
