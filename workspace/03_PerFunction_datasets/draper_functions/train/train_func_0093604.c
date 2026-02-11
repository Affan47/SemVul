Initialize(const b2SimplexCache* cache,
		const b2DistanceProxy* proxyA, const b2Sweep& sweepA,
		const b2DistanceProxy* proxyB, const b2Sweep& sweepB,
		qreal t1)
	{
		m_proxyA = proxyA;
		m_proxyB = proxyB;
		int32 count = cache->count;
		b2Assert(0 < count && count < 3);

		m_sweepA = sweepA;
		m_sweepB = sweepB;

		b2Transform xfA, xfB;
		m_sweepA.GetTransform(&xfA, t1);
		m_sweepB.GetTransform(&xfB, t1);

		if (count == 1)
		{
			m_type = e_points;
			b2Vec2 localPointA = m_proxyA->GetVertex(cache->indexA[0]);
			b2Vec2 localPointB = m_proxyB->GetVertex(cache->indexB[0]);
			b2Vec2 pointA = b2Mul(xfA, localPointA);
			b2Vec2 pointB = b2Mul(xfB, localPointB);
			m_axis = pointB - pointA;
			qreal s = m_axis.Normalize();
			return s;
		}
		else if (cache->indexA[0] == cache->indexA[1])
		{

			m_type = e_faceB;
			b2Vec2 localPointB1 = proxyB->GetVertex(cache->indexB[0]);
			b2Vec2 localPointB2 = proxyB->GetVertex(cache->indexB[1]);

			m_axis = b2Cross(localPointB2 - localPointB1, 1.0f);
			m_axis.Normalize();
			b2Vec2 normal = b2Mul(xfB.R, m_axis);

			m_localPoint = 0.5f * (localPointB1 + localPointB2);
			b2Vec2 pointB = b2Mul(xfB, m_localPoint);

			b2Vec2 localPointA = proxyA->GetVertex(cache->indexA[0]);
			b2Vec2 pointA = b2Mul(xfA, localPointA);

			qreal s = b2Dot(pointA - pointB, normal);
			if (s < 0.0f)
			{
				m_axis = -m_axis;
				s = -s;
			}
			return s;
		}
		else
		{

			m_type = e_faceA;
			b2Vec2 localPointA1 = m_proxyA->GetVertex(cache->indexA[0]);
			b2Vec2 localPointA2 = m_proxyA->GetVertex(cache->indexA[1]);

			m_axis = b2Cross(localPointA2 - localPointA1, 1.0f);
			m_axis.Normalize();
			b2Vec2 normal = b2Mul(xfA.R, m_axis);

			m_localPoint = 0.5f * (localPointA1 + localPointA2);
			b2Vec2 pointA = b2Mul(xfA, m_localPoint);

			b2Vec2 localPointB = m_proxyB->GetVertex(cache->indexB[0]);
			b2Vec2 pointB = b2Mul(xfB, localPointB);

			qreal s = b2Dot(pointB - pointA, normal);
			if (s < 0.0f)
			{
				m_axis = -m_axis;
				s = -s;
			}
			return s;
		}
	}
