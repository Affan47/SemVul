add(Animation* a)
{
    if (!m_timer.isActive()) {
        startTimer();
    }
    AnimationGroup::add(a);
}
