ProcessEvent(wxEvent& event)
{
    if ( event.GetEventType() == wxEVT_SIZE )
    {
        if ( m_ctrl )
        {

            wxSize sz = GetSize();
            m_ctrl->SetSize(sz.x+(m_xadj*2),sz.y+(m_yadj*2));
            event.Skip();
            return false;
        }
    }
    return wxWindow::ProcessEvent(event);
}
