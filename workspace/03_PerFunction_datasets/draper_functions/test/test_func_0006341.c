OnPageChanging(wxWizardEvent& event)
{
    Manager::Get()->GetConfigManager(_T("scripts"))->Write(_T("/generic_wizard/") + m_PageName + _T("/skip"), (bool)m_SkipPage);

    try
    {
        wxString sig = _T("OnLeave_") + m_PageName;
        SqPlus::SquirrelFunction<bool> cb(cbU2C(sig));
        if (cb.func.IsNull())
            return;
        bool allow = cb(event.GetDirection() != 0);
        if (!allow)
            event.Veto();
    }
    catch (SquirrelError& e)
    {
        Manager::Get()->GetScriptingManager()->DisplayErrors(&e);
    }
}
