SolvePositionConstraints(qreal baumgarte)
{
	B2_NOT_USED(baumgarte);

	if (m_frequencyHz > 0.0f)
	{

		return true;
	}

	b2Body* b1 = m_bodyA;
	b2Body* b2 = m_bodyB;

	b2Vec2 r1 = b2Mul(b1->GetTransform().R, m_localAnchor1 - b1->GetLocalCenter());
	b2Vec2 r2 = b2Mul(b2->GetTransform().R, m_localAnchor2 - b2->GetLocalCenter());

	b2Vec2 d = b2->m_sweep.c + r2 - b1->m_sweep.c - r1;

	qreal length = d.Normalize();
	qreal C = length - m_length;
	C = b2Clamp(C, -b2_maxLinearCorrection, b2_maxLinearCorrection);

	qreal impulse = -m_mass * C;
	m_u = d;
	b2Vec2 P = impulse * m_u;

	b1->m_sweep.c -= b1->m_invMass * P;
	b1->m_sweep.a -= b1->m_invI * b2Cross(r1, P);
	b2->m_sweep.c += b2->m_invMass * P;
	b2->m_sweep.a += b2->m_invI * b2Cross(r2, P);

	b1->SynchronizeTransform();
	b2->SynchronizeTransform();

	return b2Abs(C) < b2_linearSlop;
}
