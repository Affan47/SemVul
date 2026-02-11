TestPoint(const b2Transform& xf, const b2Vec2& p) const
{
	b2Vec2 pLocal = b2MulT(xf.R, p - xf.position);

	for (int32 i = 0; i < m_vertexCount; ++i)
	{
		qreal dot = b2Dot(m_normals[i], pLocal - m_vertices[i]);
		if (dot > 0.0f)
		{
			return false;
		}
	}

	return true;
}
