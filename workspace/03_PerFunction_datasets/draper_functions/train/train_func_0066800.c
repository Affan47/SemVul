OnExecTerminate(wxProcessEvent &)
{
    ReadStream(true);
    m_exec_timer->Stop();
    delete m_exec_timer;
    delete m_exec_proc;
    m_exec_proc=NULL;
    m_exec_cond->Signal();
    m_exec_mutex->Unlock();
}
