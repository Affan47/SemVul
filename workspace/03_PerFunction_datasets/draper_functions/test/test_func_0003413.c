DoSearchZombieChow()
    {
        for (GuidList::const_iterator itr = m_lZombieChowGuidList.begin(); itr != m_lZombieChowGuidList.end(); ++itr)
        {
            if (Creature* pZombie = m_creature->GetMap()->GetCreature(*itr))
            {
                if (!pZombie->IsAlive())
                {
                    continue;
                }


                if (pZombie->IsWithinDistInMap(m_creature, 15.0f))
                {
                    m_creature->DealDamage(pZombie, pZombie->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                }
            }
        }
    }
