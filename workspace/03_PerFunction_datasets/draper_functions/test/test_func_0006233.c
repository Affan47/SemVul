internalSingleStepSimulation(btScalar timeStep)
{

	BT_PROFILE("internalSingleStepSimulation");

	if(0 != m_internalPreTickCallback) {
		(*m_internalPreTickCallback)(this, timeStep);
	}


	predictUnconstraintMotion(timeStep);

	btDispatcherInfo& dispatchInfo = getDispatchInfo();

	dispatchInfo.m_timeStep = timeStep;
	dispatchInfo.m_stepCount = 0;
	dispatchInfo.m_debugDraw = getDebugDrawer();


	performDiscreteCollisionDetection();

	calculateSimulationIslands();


	getSolverInfo().m_timeStep = timeStep;


	solveConstraints(getSolverInfo());


	integrateTransforms(timeStep);


	updateActions(timeStep);

	updateActivationState( timeStep );

	if(0 != m_internalTickCallback) {
		(*m_internalTickCallback)(this, timeStep);
	}
}
