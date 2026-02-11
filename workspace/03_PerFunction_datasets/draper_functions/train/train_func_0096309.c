ShouldCollide(const b2Body* other) const
{

	if (m_type != b2_dynamicBody && other->m_type != b2_dynamicBody)
	{
		return false;
	}


	for (b2JointEdge* jn = m_jointList; jn; jn = jn->next)
	{
		if (jn->other == other)
		{
			if (jn->joint->m_collideConnected == false)
			{
				return false;
			}
		}
	}

	return true;
}
