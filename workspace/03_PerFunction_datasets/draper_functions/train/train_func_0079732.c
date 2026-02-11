stopAnimation()
{
	if (m_anim != 0 && m_anim->state() == QAbstractAnimation::Running)
		m_anim->setCurrentTime(m_anim->totalDuration());
}
