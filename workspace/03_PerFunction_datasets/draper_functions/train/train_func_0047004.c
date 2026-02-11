FindNext(bool goingDown, cbStyledTextCtrl* control, cbFindReplaceData* data)
{
    if (!control)
    {
        ScbEditor* ed = GetBuiltinEditor(GetActiveEditor());
        if (ed)
            control = ed->GetControl();
    }
    if (!control)
        return -1;

    if (!data)
    {
        data = m_LastFindReplaceData;

        if(data) data->findInFiles = false;
    }

    if (!data)
        return ShowFindDialog(false, false);

    if(!data->findInFiles)
    {
        wxString phraseAtCursor = control->GetSelectedText();

        if ( not data->findUsesSelectedText )
        {

            if (!phraseAtCursor.IsEmpty() && data->findText.IsEmpty())
                data->findText = phraseAtCursor;
        }
        else
        {

            if (!phraseAtCursor.IsEmpty())
            {
                data->findText = phraseAtCursor;
                data->originEntireScope = false;
                data->scope = 0;
            }
        }
    }

    data->directionDown = goingDown;
    return Find(control, data);
}
