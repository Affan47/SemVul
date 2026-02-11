RecordMarksFrom(BrowseMarks& otherBrowse_Marks)

{


    EditorBase* eb = m_pEdMgr->GetEditor(m_filePath);
    #if defined(LOGGING)
    if (not eb) asm("int3");
    #endif
    if (not eb) return;
    cbEditor* cbed = Manager::Get()->GetEditorManager()->GetBuiltinEditor(eb);
    if (not cbed) return;
    cbStyledTextCtrl* control = cbed->GetControl();
    for (int i=0; i<MaxEntries; ++i)
    {
        int posn = otherBrowse_Marks.GetMark(i);
        if ( posn != -1 )
        {
            #if defined(LOGGING)

            #endif
            RecordMark( posn );
            int line = control->LineFromPosition(posn);

            control->MarkerAdd(line, GetBrowseMarkerId());
        }
    }
}
