OnUpdateTools(wxUpdateUIEvent &event)
{
    bool checked = (event.GetId() == idMenuInfoPrintElementsUnlimited && m_printElements==0) ||
                   (event.GetId() == idMenuInfoPrintElements20 && m_printElements==20) ||
                   (event.GetId() == idMenuInfoPrintElements50 && m_printElements==50) ||
                   (event.GetId() == idMenuInfoPrintElements100 && m_printElements==100);
    event.Check(checked);
    event.Enable(IsRunning() && IsStopped());
}
