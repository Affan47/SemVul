processCollision (btCollisionObject* col0,btCollisionObject* col1,const btDispatcherInfo& dispatchInfo,btManifoldResult* resultOut)
{
	(void)dispatchInfo;

	if (!m_manifoldPtr)
		return;

	resultOut->setPersistentManifold(m_manifoldPtr);

	btSphereShape* sphere0 = (btSphereShape*)col0->getCollisionShape();
	btSphereShape* sphere1 = (btSphereShape*)col1->getCollisionShape();

	btVector3 diff = col0->getWorldTransform().getOrigin()-  col1->getWorldTransform().getOrigin();
	btScalar len = diff.length();
	btScalar radius0 = sphere0->getRadius();
	btScalar radius1 = sphere1->getRadius();

#ifdef CLEAR_MANIFOLD
	m_manifoldPtr->clearManifold();
#endif


	if ( len > (radius0+radius1))
	{
#ifndef CLEAR_MANIFOLD
		resultOut->refreshContactPoints();
#endif
		return;
	}

	btScalar dist = len - (radius0+radius1);

	btVector3 normalOnSurfaceB(1,0,0);
	if (len > SIMD_EPSILON)
	{
		normalOnSurfaceB = diff / len;
	}


	btVector3 pos1 = col1->getWorldTransform().getOrigin() + radius1* normalOnSurfaceB;


	resultOut->addContactPoint(normalOnSurfaceB,pos1,dist);

#ifndef CLEAR_MANIFOLD
	resultOut->refreshContactPoints();
#endif

}
