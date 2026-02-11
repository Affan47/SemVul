AttachToProcess(const wxString& pid)
{
    if (!pid.IsEmpty())
    {
        pid.ToLong((long*)&m_PidToAttach);
        Debug(false);
    }
}
