DoNextCombatManeuverPVP(Unit* pTarget)
{
    DropTotems();
    CheckShields();
    UseCooldowns();

    Player* healTarget = (m_ai->GetScenarioType() == PlayerbotAI::SCENARIO_PVP_DUEL) ? GetHealTarget() : m_bot;
    if (HealPlayer(healTarget) & (RETURN_NO_ACTION_OK | RETURN_CONTINUE))
        return RETURN_CONTINUE;
    if (m_ai->CastSpell(LIGHTNING_BOLT))
        return RETURN_CONTINUE;

    return DoNextCombatManeuverPVE(pTarget);
}
