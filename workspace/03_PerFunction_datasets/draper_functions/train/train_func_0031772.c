stop()
{
    while (!m_animations.isEmpty()) {
        m_animations.head()->stop();
        delete m_animations.dequeue();
    }
}
