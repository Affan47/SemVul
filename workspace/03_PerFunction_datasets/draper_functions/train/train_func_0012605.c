LoadSettings()
{
    bool needAutoDetection = false;
    for (size_t i = 0; i < Compilers.GetCount(); ++i)
    {
        wxString baseKey = Compilers[i]->GetParentID().IsEmpty() ? _T("/sets") : _T("/user_sets");
        Compilers[i]->LoadSettings(baseKey);

        CodeBlocksEvent event(cbEVT_COMPILER_SETTINGS_CHANGED);
        event.SetString(Compilers[i]->GetID());
        event.SetInt(static_cast<int>(i));
        event.SetClientData(static_cast<void*>(Compilers[i]));
        Manager::Get()->ProcessEvent(event);

        if (Compilers[i]->GetMasterPath().IsEmpty())
        {
            Manager::Get()->GetLogManager()->DebugLog(F(_T("Master path of compiler ID \"%s\" is empty -> triggers auto-detection."), Compilers[i]->GetID().wx_str()));
            needAutoDetection = true;
        }
    }


    if (needAutoDetection)
    {
        AutoDetectCompilers adc(Manager::Get()->GetAppWindow());
        PlaceWindow(&adc);
        adc.ShowModal();
        adc.Raise();
    }
}
