canSafeTeleport() const
{
	return m_rules->safeTeleportEnabled()
	       && m_energy >= m_rules->costOfSafeTeleport();
}
