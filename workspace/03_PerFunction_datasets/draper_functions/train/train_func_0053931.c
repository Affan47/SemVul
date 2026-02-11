HasInput()
{
    if (IsErrorAvailable())
    {
        cbTextInputStream serr(*GetErrorStream());

        wxString msg;
        msg << serr.ReadLine();

        CodeBlocksEvent event(cbEVT_PIPEDPROCESS_STDERR, m_Id);
        event.SetString(msg);
        wxPostEvent(m_Parent, event);


        return true;
    }

    if (IsInputAvailable())
    {
        cbTextInputStream sout(*GetInputStream());

        wxString msg;
        msg << sout.ReadLine();

        CodeBlocksEvent event(cbEVT_PIPEDPROCESS_STDOUT, m_Id);
        event.SetString(msg);
        wxPostEvent(m_Parent, event);


        return true;
    }

    return false;
}
