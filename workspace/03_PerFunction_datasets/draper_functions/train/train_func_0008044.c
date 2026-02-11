IsVisible(Unit* pWho) const
{
    return pWho && m_creature->IsWithinDist(pWho, VISIBLE_RANGE)
           && pWho->IsVisibleForOrDetect(m_creature, m_creature, true);
}
