destroyBox()
{
    delete m_maxValues;
    delete m_neighbors;
    delete m_stack;
    while (! m_undoList.isEmpty()) {
	discard (m_undoList.takeLast());
    }
}
