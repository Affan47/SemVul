SearchGotoLine()

{
    ScbEditor* ed = GetEditorManager()->GetBuiltinActiveEditor();
    if (!ed)
        return;

    int max = ed->GetControl()->LineFromPosition(ed->GetControl()->GetLength()) + 1;


    wxString strLine = wxGetTextFromUser( wxString::Format(_("Line (1 - %d): "), max),
                                        _("Goto line"),
                                        _T( "" ),
                                        this );
    long int line = 0;
    strLine.ToLong(&line);
    if ( line >= 1 && line <= max )
    {
        ed->UnfoldBlockFromLine(line - 1);
        ed->GotoLine(line - 1);
    }
}
