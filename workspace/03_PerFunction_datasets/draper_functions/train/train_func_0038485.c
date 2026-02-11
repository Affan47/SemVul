applyGravity()
{

	for ( int i=0;i<m_nonStaticRigidBodies.size();i++)
	{
		btRigidBody* body = m_nonStaticRigidBodies[i];
		if (body->isActive())
		{
			body->applyGravity();
		}
	}
}
