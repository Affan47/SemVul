updateEffectiveTime(int currentTime)
{
    if (m_under.data()) {
        qreal delta = currentTime / qreal(duration());

        if (m_under.data()->isIconBigger()) {
            m_under.data()->setScale(delta);
        } else {
            m_under.data()->setScale(delta);
            delta = (1 - m_endScale) * delta;
            m_under.data()->setScale(1 - delta);
        }

        delta = currentTime / qreal(duration());
        if (direction() == Forward) {
            m_under.data()->setOpacity(1.0 - delta);
        } else if (direction() == Backward) {
            m_under.data()->setOpacity(delta);
        }
    }
}

}
