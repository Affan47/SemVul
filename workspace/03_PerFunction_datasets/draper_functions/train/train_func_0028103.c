cxxtools_system_application_sighandler(int sigNo)
{
    if (cxxtools_signal_pipe)
    {
        cxxtools_signal_pipe->in().ioimpl().sigwrite(sigNo);
    }
}
