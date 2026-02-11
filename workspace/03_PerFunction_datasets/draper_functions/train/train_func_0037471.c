isAnimating() const
{
    return (m_bornTimeLine.state() == QTimeLine::Running
            || m_moveTimeLine.state() == QTimeLine::Running
            || m_removeTimeLine.state() == QTimeLine::Running);
}
