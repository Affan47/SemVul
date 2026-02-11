OnListItemActivated(wxListEvent &event)
{
    if ( !m_table ) return;

    long idx = event.GetIndex();

    CscopeEntryData data = m_table->at(idx);

    cbEditor *ed = Manager::Get()->GetEditorManager()->Open( data.GetFile() );
    if ( ed )
        ed->GotoLine(data.GetLine()-1);
    event.Skip();
}
