OnEditToggleCommentSelected(cb_unused wxCommandEvent& event)
{
    cbEditor* ed = Manager::Get()->GetEditorManager()->GetBuiltinActiveEditor();
    if (ed)
    {
        cbStyledTextCtrl* stc = ed->GetControl();
        wxString comment =
            Manager::Get()->GetEditorManager()->GetColourSet()->GetCommentToken( ed->GetLanguage() ).lineComment;
        if (comment==wxEmptyString)
            return;

        stc->BeginUndoAction();
        if ( wxSCI_INVALID_POSITION != stc->GetSelectionStart() )
        {
            int startLine = stc->LineFromPosition( stc->GetSelectionStart() );
            int endLine   = stc->LineFromPosition( stc->GetSelectionEnd() );
            int curLine   = startLine;


            if (startLine != endLine &&
            stc->GetColumn( stc->GetSelectionEnd() ) == 0)
            {


                --endLine;
            }

            bool doComment = false;
            while( curLine <= endLine )
            {

                wxString strLine = stc->GetLine( curLine );
                int commentPos = strLine.Strip( wxString::leading ).Find( comment );

                if (commentPos != 0)
                {


                    doComment = true;
                    break;
                }
                ++curLine;
            }

            curLine = startLine;
            while( curLine <= endLine )
            {
                if (doComment)
                    stc->InsertText( stc->PositionFromLine( curLine ), comment );
                else
                {

                    wxString strLine = stc->GetLine( curLine );
                    int Pos = strLine.Find(comment);
                    int start = stc->PositionFromLine( curLine ) + Pos;
                    int end = start + comment.Length();
                    stc->SetTargetStart( start );
                    stc->SetTargetEnd( end );
                    stc->ReplaceTarget( wxEmptyString );
                }
                ++curLine;
            }
            stc->SetSelectionVoid(stc->PositionFromLine(startLine),stc->PositionFromLine(endLine)+stc->LineLength(endLine));
        }
        stc->EndUndoAction();
    }
}
