SetType(b2BodyType type)
{
	if (m_type == type)
	{
		return;
	}

	m_type = type;

	ResetMassData();

	if (m_type == b2_staticBody)
	{
		m_linearVelocity.SetZero();
		m_angularVelocity = 0.0f;
	}

	SetAwake(true);

	m_force.SetZero();
	m_torque = 0.0f;


	for (b2ContactEdge* ce = m_contactList; ce; ce = ce->next)
	{
		ce->contact->FlagForFiltering();
	}
}
