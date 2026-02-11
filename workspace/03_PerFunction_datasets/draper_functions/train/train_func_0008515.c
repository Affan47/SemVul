get_time_in_mcsec()
{
#if defined(_WIN32)
    if(!m_stopped)
        QueryPerformanceCounter(&m_ecount);

    m_stime = m_scount.QuadPart * (1000000.0 / m_freq.QuadPart);
    m_etime = m_ecount.QuadPart * (1000000.0 / m_freq.QuadPart);
#elif defined(__linux) || defined(__unix) || defined (__posix)
    if(!m_stopped)
        gettimeofday(&m_ecount, NULL);

    m_stime = (m_scount.tv_sec * 1000000.0) + m_scount.tv_usec;
    m_etime = (m_ecount.tv_sec * 1000000.0) + m_ecount.tv_usec;
#endif

    return m_etime - m_stime;
}
