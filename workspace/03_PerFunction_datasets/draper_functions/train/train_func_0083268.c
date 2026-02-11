OnApply()
{
    ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("byogames"));
    cfg->Write(_T("/ismaxplaytime"),(bool)m_MaxPlaytimeChk->GetValue());
    cfg->Write(_T("/maxplaytime"),(int)m_MaxPlaytimeSpn->GetValue());
    cfg->Write(_T("/isminworktime"),(bool)m_MinWorkChk->GetValue());
    cfg->Write(_T("/minworktime"),(int)m_MinWorkSpn->GetValue());
    cfg->Write(_T("/isoverworktime"),(bool)m_OverworkChk->GetValue());
    cfg->Write(_T("/overworktime"),(int)m_OverworkSpn->GetValue());
    cfg->Write(_T("/col01"),m_Col1->GetBackgroundColour());
    cfg->Write(_T("/col02"),m_Col2->GetBackgroundColour());
    cfg->Write(_T("/col03"),m_Col3->GetBackgroundColour());
    cfg->Write(_T("/col04"),m_Col4->GetBackgroundColour());
    cfg->Write(_T("/col05"),m_Col5->GetBackgroundColour());
    cfg->Write(_T("/col06"),m_Col6->GetBackgroundColour());

    byoGameBase::ReloadFromConfig();
}
