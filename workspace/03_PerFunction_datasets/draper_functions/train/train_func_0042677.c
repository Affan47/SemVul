solveAngularLimits(
	btScalar timeStep,btVector3& axis,btScalar jacDiagABInv,
	btRigidBody * body0, btRigidBody * body1 )
{
	if (needApplyTorques()==false) return 0.0f;

	btScalar target_velocity = m_targetVelocity;
	btScalar maxMotorForce = m_maxMotorForce;


	if (m_currentLimit!=0)
	{
		target_velocity = -m_stopERP*m_currentLimitError/(timeStep);
		maxMotorForce = m_maxLimitForce;
	}

	maxMotorForce *= timeStep;


	btVector3 angVelA;
	body0->internalGetAngularVelocity(angVelA);
	btVector3 angVelB;
	body1->internalGetAngularVelocity(angVelB);

	btVector3 vel_diff;
	vel_diff = angVelA-angVelB;


	btScalar rel_vel = axis.dot(vel_diff);


	btScalar motor_relvel = m_limitSoftness*(target_velocity  - m_damping*rel_vel);


	if ( motor_relvel < SIMD_EPSILON && motor_relvel > -SIMD_EPSILON  )
	{
		return 0.0f;
	}


	btScalar unclippedMotorImpulse = (1+m_bounce)*motor_relvel*jacDiagABInv;


	btScalar clippedMotorImpulse;


	if (unclippedMotorImpulse>0.0f)
	{
		clippedMotorImpulse =  unclippedMotorImpulse > maxMotorForce? maxMotorForce: unclippedMotorImpulse;
	}
	else
	{
		clippedMotorImpulse =  unclippedMotorImpulse < -maxMotorForce ? -maxMotorForce: unclippedMotorImpulse;
	}


	btScalar	lo = btScalar(-BT_LARGE_FLOAT);
	btScalar	hi = btScalar(BT_LARGE_FLOAT);

	btScalar oldaccumImpulse = m_accumulatedImpulse;
	btScalar sum = oldaccumImpulse + clippedMotorImpulse;
	m_accumulatedImpulse = sum > hi ? btScalar(0.) : sum < lo ? btScalar(0.) : sum;

	clippedMotorImpulse = m_accumulatedImpulse - oldaccumImpulse;

	btVector3 motorImp = clippedMotorImpulse * axis;


	body0->internalApplyImpulse(btVector3(0,0,0), body0->getInvInertiaTensorWorld()*axis,clippedMotorImpulse);
	body1->internalApplyImpulse(btVector3(0,0,0), body1->getInvInertiaTensorWorld()*axis,-clippedMotorImpulse);


	return clippedMotorImpulse;


}
