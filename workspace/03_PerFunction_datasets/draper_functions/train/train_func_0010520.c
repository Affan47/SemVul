stepDown ( btCollisionWorld* collisionWorld, btScalar dt)
{
	btTransform start, end;


	btVector3 step_drop = getUpAxisDirections()[m_upAxis] * m_currentStepOffset;
	btVector3 gravity_drop = getUpAxisDirections()[m_upAxis] * m_stepHeight;
	m_targetPosition -= (step_drop + gravity_drop);

	start.setIdentity ();
	end.setIdentity ();

	start.setOrigin (m_currentPosition);
	end.setOrigin (m_targetPosition);

	btKinematicClosestNotMeConvexResultCallback callback (m_ghostObject);
	callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
	callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;

	if (m_useGhostObjectSweepTest)
	{
		m_ghostObject->convexSweepTest (m_convexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
	} else
	{
		collisionWorld->convexSweepTest (m_convexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
	}

	if (callback.hasHit())
	{

		m_currentPosition.setInterpolate3 (m_currentPosition, m_targetPosition, callback.m_closestHitFraction);
	} else {


		m_currentPosition = m_targetPosition;
	}
}
