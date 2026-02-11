BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* )
{
    if ( !IsAttached() || m_pProcess) return;

    if(type != mtEditorManager || !menu ) return;

    EditorManager* emngr = Manager::Get()->GetEditorManager();
    if ( !emngr ) return;

    EditorBase *edb = emngr->GetActiveEditor();
    if ( !edb || !edb->IsBuiltinEditor() ) return;

    cbStyledTextCtrl* stc = ((cbEditor*)edb)->GetControl();
    if ( !stc ) return;

    if ( stc->GetLexer()  != wxSCI_LEX_CPP) return;

    wxString word = GetWordAtCaret();
    if ( word.IsEmpty() ) return;


    const wxMenuItemList ItemsList = menu->GetMenuItems();
    int idximp=-1;
    int idxocc=-1;
    for (int idx = 0; idx < (int)ItemsList.GetCount(); ++idx)
    {
        #if wxCHECK_VERSION(2, 9, 0)
        if (ItemsList[idx]->GetItemLabelText().StartsWith(_("Find implementation of:")) )
        #else
        if (ItemsList[idx]->GetLabel().StartsWith(_("Find implementation of:")) )
        #endif
        {
            idximp = idx;
        }
        #if wxCHECK_VERSION(2, 9, 0)
        if (ItemsList[idx]->GetItemLabelText().StartsWith(_("Find occurrences of:")) )
        #else
        if (ItemsList[idx]->GetLabel().StartsWith(_("Find occurrences of:")) )
        #endif
        {
            idxocc = idx;
        }
    }

    if ( idxocc == -1 && idximp == -1 )
    {

        menu->AppendSeparator();


        menu->Append(idOnFindFunctionsCalledByThisFuncion, _("Find functions called by '") + word + _T("'"));
        menu->Append(idOnFindFunctionsCallingThisFunction, _("Find functions calling '") + word + _T("'"));
    }
    else
    {
        if ( idxocc >= 0 )
            idximp = idxocc;


        menu->Insert(++idximp,idOnFindFunctionsCalledByThisFuncion, _("Find functions called by '") + word + _T("'"));
        menu->Insert(++idximp,idOnFindFunctionsCallingThisFunction, _("Find functions calling '") + word + _T("'"));
    }
}
