setGravity(const btVector3& gravity)
{
	m_gravity = gravity;
	for ( int i=0;i<m_nonStaticRigidBodies.size();i++)
	{
		btRigidBody* body = m_nonStaticRigidBodies[i];
		if (body->isActive() && !(body->getFlags() &BT_DISABLE_WORLD_GRAVITY))
		{
			body->setGravity(gravity);
		}
	}
}
