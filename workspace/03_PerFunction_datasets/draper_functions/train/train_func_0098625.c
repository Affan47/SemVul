doWait()
{
    SE_LOG_DEBUG(NULL, "D-Bus transport: wait - old state: %s, %s",
                 SessionCommon::ConnectionStateToString(m_state).c_str(),
                 m_error.c_str());
    if (SuspendFlags::getSuspendFlags().getState() == SuspendFlags::NORMAL) {


        g_main_context_iteration(NULL, true);
    }
    SE_LOG_DEBUG(NULL, "D-Bus transport: wait - new state: %s, %s",
                 SessionCommon::ConnectionStateToString(m_state).c_str(),
                 m_error.c_str());
}
