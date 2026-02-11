ComputePolygonSeparation()
{
	b2EPAxis axis;
	axis.type = b2EPAxis::e_unknown;
	axis.index = -1;
	axis.separation = -FLT_MAX;
	for (int32 i = 0; i < m_proxyB.count; ++i)
	{
		b2Vec2 n = -m_proxyB.normals[i];


		bool valid1 = b2Cross(n, m_limit11) >= -b2_angularSlop && b2Cross(m_limit12, n) >= -b2_angularSlop;
		bool valid2 = b2Cross(n, m_limit21) >= -b2_angularSlop && b2Cross(m_limit22, n) >= -b2_angularSlop;

		if (valid1 == false && valid2 == false)
		{
			continue;
		}

		qreal s1 = b2Dot(n, m_proxyB.vertices[i] - m_edgeA.v1);
		qreal s2 = b2Dot(n, m_proxyB.vertices[i] - m_edgeA.v2);
		qreal s = b2Min(s1, s2);

		if (s > m_radius)
		{
			axis.type = b2EPAxis::e_edgeB;
			axis.index = i;
			axis.separation = s;
		}

		if (s > axis.separation)
		{
			axis.type = b2EPAxis::e_edgeB;
			axis.index = i;
			axis.separation = s;
		}
	}

	return axis;
}
