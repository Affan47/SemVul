Prepare(btScalar dt,int iterations)
{
	Joint::Prepare(dt,iterations);
	const bool	dodrift=(m_life==0);
	m_delete=(++m_life)>m_maxlife;
	if(dodrift)
	{
		m_drift=m_drift*m_erp/dt;
		if(m_split>0)
		{
			m_sdrift	=	m_massmatrix*(m_drift*m_split);
			m_drift		*=	1-m_split;
		}
		m_drift/=(btScalar)iterations;
	}
	else
	{
		m_drift=m_sdrift=btVector3(0,0,0);
	}
}
