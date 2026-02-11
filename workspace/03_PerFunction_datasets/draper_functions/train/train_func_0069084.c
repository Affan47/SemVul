coneLocalSupport(const btVector3& v) const
{

	btScalar halfHeight = m_height * btScalar(0.5);

 if (v[m_coneIndices[1]] > v.length() * m_sinAngle)
 {
	btVector3 tmp;

	tmp[m_coneIndices[0]] = btScalar(0.);
	tmp[m_coneIndices[1]] = halfHeight;
	tmp[m_coneIndices[2]] = btScalar(0.);
	return tmp;
 }
  else {
    btScalar s = btSqrt(v[m_coneIndices[0]] * v[m_coneIndices[0]] + v[m_coneIndices[2]] * v[m_coneIndices[2]]);
    if (s > SIMD_EPSILON) {
      btScalar d = m_radius / s;
	  btVector3 tmp;
	  tmp[m_coneIndices[0]] = v[m_coneIndices[0]] * d;
	  tmp[m_coneIndices[1]] = -halfHeight;
	  tmp[m_coneIndices[2]] = v[m_coneIndices[2]] * d;
	  return tmp;
    }
    else  {
		btVector3 tmp;
		tmp[m_coneIndices[0]] = btScalar(0.);
		tmp[m_coneIndices[1]] = -halfHeight;
		tmp[m_coneIndices[2]] = btScalar(0.);
		return tmp;
	}
  }

}
