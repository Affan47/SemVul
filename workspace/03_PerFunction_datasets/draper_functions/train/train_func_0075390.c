InitVelocityConstraints(const b2TimeStep& step)
{
	b2Body* bA = m_bodyA;
	b2Body* bB = m_bodyB;


	b2Vec2 rA = b2Mul(bA->GetTransform().R, m_localAnchorA - bA->GetLocalCenter());
	b2Vec2 rB = b2Mul(bB->GetTransform().R, m_localAnchorB - bB->GetLocalCenter());


	qreal mA = bA->m_invMass, mB = bB->m_invMass;
	qreal iA = bA->m_invI, iB = bB->m_invI;

	b2Mat22 K1;
	K1.col1.x = mA + mB;	K1.col2.x = 0.0f;
	K1.col1.y = 0.0f;		K1.col2.y = mA + mB;

	b2Mat22 K2;
	K2.col1.x =  iA * rA.y * rA.y;	K2.col2.x = -iA * rA.x * rA.y;
	K2.col1.y = -iA * rA.x * rA.y;	K2.col2.y =  iA * rA.x * rA.x;

	b2Mat22 K3;
	K3.col1.x =  iB * rB.y * rB.y;	K3.col2.x = -iB * rB.x * rB.y;
	K3.col1.y = -iB * rB.x * rB.y;	K3.col2.y =  iB * rB.x * rB.x;

	b2Mat22 K = K1 + K2 + K3;
	m_linearMass = K.GetInverse();

	m_angularMass = iA + iB;
	if (m_angularMass > 0.0f)
	{
		m_angularMass = 1.0f / m_angularMass;
	}

	if (step.warmStarting)
	{

		m_linearImpulse *= step.dtRatio;
		m_angularImpulse *= step.dtRatio;

		b2Vec2 P(m_linearImpulse.x, m_linearImpulse.y);

		bA->m_linearVelocity -= mA * P;
		bA->m_angularVelocity -= iA * (b2Cross(rA, P) + m_angularImpulse);

		bB->m_linearVelocity += mB * P;
		bB->m_angularVelocity += iB * (b2Cross(rB, P) + m_angularImpulse);
	}
	else
	{
		m_linearImpulse.SetZero();
		m_angularImpulse = 0.0f;
	}
}
