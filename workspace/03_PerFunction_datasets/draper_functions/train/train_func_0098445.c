SolveTOIPositionConstraints(qreal baumgarte, const b2Body* toiBodyA, const b2Body* toiBodyB)
{
	qreal minSeparation = 0.0f;

	for (int32 i = 0; i < m_count; ++i)
	{
		b2ContactConstraint* c = m_constraints + i;
		b2Body* bodyA = c->bodyA;
		b2Body* bodyB = c->bodyB;

		qreal massA = 0.0f;
		if (bodyA == toiBodyA || bodyA == toiBodyB)
		{
			massA = bodyA->m_mass;
		}

		qreal massB = 0.0f;
		if (bodyB == toiBodyA || bodyB == toiBodyB)
		{
			massB = bodyB->m_mass;
		}

		qreal invMassA = bodyA->m_mass * bodyA->m_invMass;
		qreal invIA = bodyA->m_mass * bodyA->m_invI;
		qreal invMassB = bodyB->m_mass * bodyB->m_invMass;
		qreal invIB = bodyB->m_mass * bodyB->m_invI;


		for (int32 j = 0; j < c->pointCount; ++j)
		{
			b2PositionSolverManifold psm;
			psm.Initialize(c, j);
			b2Vec2 normal = psm.normal;

			b2Vec2 point = psm.point;
			qreal separation = psm.separation;

			b2Vec2 rA = point - bodyA->m_sweep.c;
			b2Vec2 rB = point - bodyB->m_sweep.c;


			minSeparation = b2Min(minSeparation, separation);


			qreal C = b2Clamp(baumgarte * (separation + b2_linearSlop), -b2_maxLinearCorrection, 0.0f);


			qreal rnA = b2Cross(rA, normal);
			qreal rnB = b2Cross(rB, normal);
			qreal K = invMassA + invMassB + invIA * rnA * rnA + invIB * rnB * rnB;


			qreal impulse = K > 0.0f ? - C / K : 0.0f;

			b2Vec2 P = impulse * normal;

			bodyA->m_sweep.c -= invMassA * P;
			bodyA->m_sweep.a -= invIA * b2Cross(rA, P);
			bodyA->SynchronizeTransform();

			bodyB->m_sweep.c += invMassB * P;
			bodyB->m_sweep.a += invIB * b2Cross(rB, P);
			bodyB->SynchronizeTransform();
		}
	}


	return minSeparation >= -1.5f * b2_linearSlop;
}
