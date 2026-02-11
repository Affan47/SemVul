processCollision (btCollisionObject* body0,btCollisionObject* body1,const btDispatcherInfo& dispatchInfo,btManifoldResult* resultOut)
{
	if (!m_manifoldPtr)
		return;

	btCollisionObject*	col0 = body0;
	btCollisionObject*	col1 = body1;
	btBoxShape* box0 = (btBoxShape*)col0->getCollisionShape();
	btBoxShape* box1 = (btBoxShape*)col1->getCollisionShape();


	resultOut->setPersistentManifold(m_manifoldPtr);
#ifndef USE_PERSISTENT_CONTACTS
	m_manifoldPtr->clearManifold();
#endif

	btDiscreteCollisionDetectorInterface::ClosestPointInput input;
	input.m_maximumDistanceSquared = BT_LARGE_FLOAT;
	input.m_transformA = body0->getWorldTransform();
	input.m_transformB = body1->getWorldTransform();

	btBoxBoxDetector detector(box0,box1);
	detector.getClosestPoints(input,*resultOut,dispatchInfo.m_debugDraw);

#ifdef USE_PERSISTENT_CONTACTS

	if (m_ownManifold)
	{
		resultOut->refreshContactPoints();
	}
#endif

}
