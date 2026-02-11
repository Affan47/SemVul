setTotalMass(btScalar mass,bool fromfaces)
{
	int i;

	if(fromfaces)
	{

		for(i=0;i<m_nodes.size();++i)
		{
			m_nodes[i].m_im=0;
		}
		for(i=0;i<m_faces.size();++i)
		{
			const Face&		f=m_faces[i];
			const btScalar	twicearea=AreaOf(	f.m_n[0]->m_x,
				f.m_n[1]->m_x,
				f.m_n[2]->m_x);
			for(int j=0;j<3;++j)
			{
				f.m_n[j]->m_im+=twicearea;
			}
		}
		for( i=0;i<m_nodes.size();++i)
		{
			m_nodes[i].m_im=1/m_nodes[i].m_im;
		}
	}
	const btScalar	tm=getTotalMass();
	const btScalar	itm=1/tm;
	for( i=0;i<m_nodes.size();++i)
	{
		m_nodes[i].m_im/=itm*mass;
	}
	m_bUpdateRtCst=true;
}
