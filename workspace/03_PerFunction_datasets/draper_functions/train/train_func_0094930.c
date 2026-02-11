SetSelection(int index)

{


    if ((index < 0) || (index >= MaxEntries )) return;

    EditorBase* eb = GetEditor(index);
    if (eb)
    {
        Manager::Get()->GetEditorManager()->SetActiveEditor(eb);
        #if defined(LOGGING)
        LOGIT( _T("BT SetSelection[%d] editor[%p][%s]"), index, eb, eb->GetShortName().wx_str() );
        #endif


        m_UpdateUIFocusEditor = eb;
    }
}
