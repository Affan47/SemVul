buildJacobian()
{
	if (m_useSolveConstraintObsolete)
	{
		m_appliedImpulse = btScalar(0.);
		m_accTwistLimitImpulse = btScalar(0.);
		m_accSwingLimitImpulse = btScalar(0.);
		m_accMotorImpulse = btVector3(0.,0.,0.);

		if (!m_angularOnly)
		{
			btVector3 pivotAInW = m_rbA.getCenterOfMassTransform()*m_rbAFrame.getOrigin();
			btVector3 pivotBInW = m_rbB.getCenterOfMassTransform()*m_rbBFrame.getOrigin();
			btVector3 relPos = pivotBInW - pivotAInW;

			btVector3 normal[3];
			if (relPos.length2() > SIMD_EPSILON)
			{
				normal[0] = relPos.normalized();
			}
			else
			{
				normal[0].setValue(btScalar(1.0),0,0);
			}

			btPlaneSpace1(normal[0], normal[1], normal[2]);

			for (int i=0;i<3;i++)
			{
				new (&m_jac[i]) btJacobianEntry(
				m_rbA.getCenterOfMassTransform().getBasis().transpose(),
				m_rbB.getCenterOfMassTransform().getBasis().transpose(),
				pivotAInW - m_rbA.getCenterOfMassPosition(),
				pivotBInW - m_rbB.getCenterOfMassPosition(),
				normal[i],
				m_rbA.getInvInertiaDiagLocal(),
				m_rbA.getInvMass(),
				m_rbB.getInvInertiaDiagLocal(),
				m_rbB.getInvMass());
			}
		}

		calcAngleInfo2(m_rbA.getCenterOfMassTransform(),m_rbB.getCenterOfMassTransform(),m_rbA.getInvInertiaTensorWorld(),m_rbB.getInvInertiaTensorWorld());
	}
}
