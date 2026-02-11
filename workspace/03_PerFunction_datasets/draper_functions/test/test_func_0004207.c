add(long id, bool prev, bool post)
{
	int v = 0;
	if (prev) v += 2;
	if (post) v += 1;
	m_idStates.insert(id, v);
}
