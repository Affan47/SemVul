Flush()
{
    LogEntity* log;
    while (pendingMsg_.Pop((void**)&log))
    {
        ostream* fout = log->fout;
        if (!fout->good()) continue;

        *fout << (char*)log->data << std::endl;


        buffer_.ReleaseBuffer(log);
    }
}
