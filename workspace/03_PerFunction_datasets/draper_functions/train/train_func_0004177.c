set_request(gsl_shell_thread::request_e req, const char* line)
{
    m_eval.lock();
    m_request = req;
    if (line) m_line_pending = line;
    if (m_status == waiting)
    {
        m_eval.signal();
    }
    m_eval.unlock();
    sched_yield();
}
