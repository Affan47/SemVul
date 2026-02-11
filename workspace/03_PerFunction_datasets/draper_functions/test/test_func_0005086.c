AddSC_instance_molten_core()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "instance_molten_core";
    pNewScript->GetInstanceData = &GetInstance_instance_molten_core;
    pNewScript->RegisterSelf();
}
