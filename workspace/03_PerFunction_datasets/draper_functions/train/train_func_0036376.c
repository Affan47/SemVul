OnActivate(wxActivateEvent& event)
{
    if (!event.GetActive())
    {
        if (!m_closing)
        {
            m_closing = true;
            EndModal(wxID_CANCEL);
        }
    }
}
