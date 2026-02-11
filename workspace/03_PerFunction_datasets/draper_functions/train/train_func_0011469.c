DoFirstCombatManeuverPVE(Unit* pTarget)
{
    if (!m_ai)  return RETURN_NO_ACTION_ERROR;
    if (!m_bot) return RETURN_NO_ACTION_ERROR;

    float fTargetDist = m_bot->GetCombatDistance(pTarget, true);

    if (DEFENSIVE_STANCE && (m_ai->GetCombatOrder() & PlayerbotAI::ORDERS_TANK))
    {
        if (!m_bot->HasAura(DEFENSIVE_STANCE, EFFECT_INDEX_0) && m_ai->CastSpell(DEFENSIVE_STANCE))
            return RETURN_CONTINUE;
        else if (TAUNT > 0 && m_bot->HasAura(DEFENSIVE_STANCE, EFFECT_INDEX_0) && m_ai->CastSpell(TAUNT, *pTarget))
            return RETURN_FINISHED_FIRST_MOVES;
    }

    if (BERSERKER_STANCE)
    {
        if (!m_bot->HasAura(BERSERKER_STANCE, EFFECT_INDEX_0) && m_ai->CastSpell(BERSERKER_STANCE))
            return RETURN_CONTINUE;
        if (BLOODRAGE > 0 && m_bot->HasAura(BERSERKER_STANCE, EFFECT_INDEX_0) && m_ai->GetRageAmount() <= 10)
            return m_ai->CastSpell(BLOODRAGE) ? RETURN_FINISHED_FIRST_MOVES : RETURN_NO_ACTION_ERROR;
        if (INTERCEPT > 0 && m_bot->HasAura(BERSERKER_STANCE, EFFECT_INDEX_0))
        {
            if (fTargetDist < 8.0f)
                return RETURN_NO_ACTION_OK;
            else if (fTargetDist > 25.0f)
                return RETURN_CONTINUE;
            else if (INTERCEPT > 0 && m_ai->CastSpell(INTERCEPT, *pTarget))
            {
                float x, y, z;
                pTarget->GetContactPoint(m_bot, x, y, z, 3.666666f);
                m_bot->Relocate(x, y, z);
                return RETURN_FINISHED_FIRST_MOVES;
            }
        }
    }

    if (BATTLE_STANCE)
    {
        if (!m_bot->HasAura(BATTLE_STANCE, EFFECT_INDEX_0) && m_ai->CastSpell(BATTLE_STANCE))
            return RETURN_CONTINUE;
        if (CHARGE > 0 && m_bot->HasAura(BATTLE_STANCE, EFFECT_INDEX_0))
        {
            if (fTargetDist < 8.0f)
                return RETURN_NO_ACTION_OK;
            if (fTargetDist > 25.0f)
                return RETURN_CONTINUE;
            else if (CHARGE > 0 && m_ai->CastSpell(CHARGE, *pTarget))
            {
                float x, y, z;
                pTarget->GetContactPoint(m_bot, x, y, z, 3.666666f);
                m_bot->Relocate(x, y, z);
                return RETURN_FINISHED_FIRST_MOVES;
            }
        }
    }

    return RETURN_NO_ACTION_OK;
}
