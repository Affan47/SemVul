resumeBg(t_states::iterator stateIt)
{
    if ((*stateIt)->allowBg() && stateIt != m_states.begin()) {
        t_states::iterator prev = stateIt;
        --prev;
        resumeBg(prev);
        (*prev)->noteBg();
    }

    if (!(*stateIt)->isRunning()) {
        (*stateIt)->resumeState();
    }
}
