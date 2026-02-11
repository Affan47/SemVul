GotoPreviousChanged()
{
    cbAssert(GetControl());
    cbStyledTextCtrl* p_Control = GetControl();
    int fromLine = p_Control->LineFromPosition(p_Control->GetCurrentPos());
    int toLine = 0;
    if (fromLine == toLine)
        fromLine = p_Control->GetLineCount() - 1;
    else
        fromLine--;

    int newLine = p_Control->FindChangedLine(fromLine, toLine);
    if (newLine != wxSCI_INVALID_POSITION)
    {
        p_Control->GotoLine(newLine);
        p_Control->MakeNearbyLinesVisible(p_Control->GetCurrentLine());
    }
}
