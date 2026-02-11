setUpdatesBlocked(bool blocked)
{
	if (!blocked) {
		resetScenes();
	}
	m_updates = !blocked;
}
