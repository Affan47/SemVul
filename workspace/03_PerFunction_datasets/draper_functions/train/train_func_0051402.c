pointersToIndices()
{
#define	PTR2IDX(_p_,_b_)	reinterpret_cast<btSoftBody::Node*>((_p_)-(_b_))
	btSoftBody::Node*	base=&m_nodes[0];
	int i,ni;

	for(i=0,ni=m_nodes.size();i<ni;++i)
	{
		if(m_nodes[i].m_leaf)
		{
			m_nodes[i].m_leaf->data=*(void**)&i;
		}
	}
	for(i=0,ni=m_links.size();i<ni;++i)
	{
		m_links[i].m_n[0]=PTR2IDX(m_links[i].m_n[0],base);
		m_links[i].m_n[1]=PTR2IDX(m_links[i].m_n[1],base);
	}
	for(i=0,ni=m_faces.size();i<ni;++i)
	{
		m_faces[i].m_n[0]=PTR2IDX(m_faces[i].m_n[0],base);
		m_faces[i].m_n[1]=PTR2IDX(m_faces[i].m_n[1],base);
		m_faces[i].m_n[2]=PTR2IDX(m_faces[i].m_n[2],base);
		if(m_faces[i].m_leaf)
		{
			m_faces[i].m_leaf->data=*(void**)&i;
		}
	}
	for(i=0,ni=m_anchors.size();i<ni;++i)
	{
		m_anchors[i].m_node=PTR2IDX(m_anchors[i].m_node,base);
	}
	for(i=0,ni=m_notes.size();i<ni;++i)
	{
		for(int j=0;j<m_notes[i].m_rank;++j)
		{
			m_notes[i].m_nodes[j]=PTR2IDX(m_notes[i].m_nodes[j],base);
		}
	}
#undef	PTR2IDX
}
