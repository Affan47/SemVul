applyGravity()
{
	if (isStaticOrKinematicObject())
		return;

	applyCentralForce(m_gravity);

}
