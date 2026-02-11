Cleanup ()
{
	ARRAY_FOREACH ( i, m_dSpawned )
	{
		m_dSpawned[i]->m_dChildren.Reset ();
		SafeDelete ( m_dSpawned[i] );
	}
	m_dSpawned.Reset ();
}
