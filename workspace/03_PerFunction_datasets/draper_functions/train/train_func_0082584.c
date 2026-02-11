OnCreatureDeath(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_BARONESS_ANASTARI:
            SetData(TYPE_BARONESS, DONE);
            break;
        case NPC_MALEKI_THE_PALLID:
            SetData(TYPE_PALLID, DONE);
            break;
        case NPC_NERUBENKAN:
            SetData(TYPE_NERUB, DONE);
            break;
        case NPC_RAMSTEIN:
            SetData(TYPE_RAMSTEIN, DONE);
            break;
        case NPC_BARON:
            SetData(TYPE_BARON, DONE);
            break;

        case NPC_THUZADIN_ACOLYTE:
            ThazudinAcolyteJustDied(pCreature);
            break;

        case NPC_ABOM_BILE:
        case NPC_ABOM_VENOM:

            SetData(TYPE_RAMSTEIN, SPECIAL);
            break;

        case NPC_MINDLESS_UNDEAD:
            m_luiUndeadGUIDs.remove(pCreature->GetObjectGuid());
            if (m_luiUndeadGUIDs.empty())
            {

                for (GuidList::const_iterator itr = m_luiGuardGUIDs.begin(); itr != m_luiGuardGUIDs.end(); ++itr)
                {
                    Creature* pGuard = instance->GetCreature(*itr);
                    if (pGuard && pGuard->IsAlive() && !pGuard->IsInCombat())
                    {
                        float fX, fY, fZ;
                        pGuard->GetRandomPoint(aStratholmeLocation[5].m_fX, aStratholmeLocation[5].m_fY, aStratholmeLocation[5].m_fZ, 10.0f, fX, fY, fZ);
                        pGuard->GetMotionMaster()->MovePoint(0, fX, fY, fZ);
                    }
                }
            }
            break;
        case NPC_BLACK_GUARD:
            m_luiGuardGUIDs.remove(pCreature->GetObjectGuid());
            if (m_luiGuardGUIDs.empty())
            {
                SetData(TYPE_BLACK_GUARDS, DONE);
            }

            break;


        case NPC_CRIMSON_INITIATE:
        case NPC_CRIMSON_GALLANT:
        case NPC_CRIMSON_GUARDSMAN:
        case NPC_CRIMSON_CONJURER:
            if (m_suiCrimsonLowGuids.find(pCreature->GetGUIDLow()) != m_suiCrimsonLowGuids.end())
            {
                m_suiCrimsonLowGuids.erase(pCreature->GetGUIDLow());


                if (m_suiCrimsonLowGuids.empty())
                {
                    pCreature->SummonCreature(NPC_TIMMY_THE_CRUEL, aTimmyLocation[0].m_fX, aTimmyLocation[0].m_fY, aTimmyLocation[0].m_fZ, aTimmyLocation[0].m_fO, TEMPSUMMON_DEAD_DESPAWN, 0);
                }
            }
            break;
    }
}
