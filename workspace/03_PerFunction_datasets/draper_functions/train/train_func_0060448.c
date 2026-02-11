ProcessSlave(CreatureLinkingEvent eventType, Creature* pSource, uint32 flag, Creature* pSlave, Unit* pEnemy)
{
    switch (eventType)
    {
        case LINKING_EVENT_AGGRO:
            if (flag & FLAG_AGGRO_ON_AGGRO)
            {
                if (pSlave->IsControlledByPlayer())
                    return;

                if (pSlave->isInCombat())
                    pSlave->SetInCombatWith(pEnemy);
                else
                    pSlave->AI()->AttackStart(pEnemy);
            }
            break;
        case LINKING_EVENT_EVADE:
            if (flag & FLAG_DESPAWN_ON_EVADE && pSlave->isAlive())
                pSlave->ForcedDespawn();
            if (flag & FLAG_RESPAWN_ON_EVADE && !pSlave->isAlive())
                pSlave->Respawn();
            break;
        case LINKING_EVENT_DIE:
            if (flag & FLAG_SELFKILL_ON_DEATH && pSlave->isAlive())
                pSlave->DealDamage(pSlave, pSlave->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
            if (flag & FLAG_DESPAWN_ON_DEATH && pSlave->isAlive())
                pSlave->ForcedDespawn();
            if (flag & FLAG_RESPAWN_ON_DEATH && !pSlave->isAlive())
                pSlave->Respawn();
            break;
        case LINKING_EVENT_RESPAWN:
            if (flag & FLAG_RESPAWN_ON_RESPAWN)
            {

                if (!pSlave->isAlive() && pSlave->GetRespawnTime() > time(NULL))
                    pSlave->Respawn();
            }
            else if (flag & FLAG_DESPAWN_ON_RESPAWN && pSlave->isAlive())
                pSlave->ForcedDespawn();

            if (flag & FLAG_FOLLOW && pSlave->isAlive() && !pSlave->isInCombat())
                SetFollowing(pSlave, pSource);

            break;
        case LINKING_EVENT_DESPAWN:
            if (flag & FLAG_DESPAWN_ON_DESPAWN && !pSlave->IsDespawned())
                pSlave->ForcedDespawn();

            break;
    }
}
