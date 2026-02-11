solveGroup(btCollisionObject** bodies,int numBodies,btPersistentManifold** manifoldPtr, int numManifolds,btTypedConstraint** constraints,int numConstraints,const btContactSolverInfo& infoGlobal,btIDebugDraw* debugDrawer,btStackAlloc* stackAlloc,btDispatcher* )
{

	BT_PROFILE("solveGroup");

	btAssert(bodies);
	btAssert(numBodies);

	solveGroupCacheFriendlySetup( bodies, numBodies, manifoldPtr,  numManifolds,constraints, numConstraints,infoGlobal,debugDrawer, stackAlloc);

	solveGroupCacheFriendlyIterations(bodies, numBodies, manifoldPtr,  numManifolds,constraints, numConstraints,infoGlobal,debugDrawer, stackAlloc);

	solveGroupCacheFriendlyFinish(bodies, numBodies, manifoldPtr,  numManifolds,constraints, numConstraints,infoGlobal,debugDrawer, stackAlloc);

	return 0.f;
}
