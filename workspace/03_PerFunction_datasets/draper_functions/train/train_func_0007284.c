setPaused(bool paused)
{

	const bool visible = !paused;
	if (isVisible() == visible)
		return;
	setVisible(visible);
	QList<QAbstractAnimation*>::const_iterator it1 = m_runningAnimations.constBegin(), it2 = m_runningAnimations.constEnd();
	for (; it1 != it2; ++it1)
		(*it1)->setPaused(paused);
}
