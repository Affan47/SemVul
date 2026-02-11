flush_queue()
{
	while (!m_queue.empty()) {
		m_queue.pop();
	}
}
