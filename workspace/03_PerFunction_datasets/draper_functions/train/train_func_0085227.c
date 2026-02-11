HandleChildKey( wxKeyEvent& event )
{
    bool res = true;

    wxPGProperty* selected = GetSelection();

    if ( !selected || !m_wndEditor )
    {
        return true;
    }

    int action = KeyEventToAction(event);


    if ( action == wxPG_ACTION_CANCEL_EDIT )
    {


        if ( IsEditorsValueModified() )
        {
            EditorsValueWasNotModified();


            selected->GetEditorClass()->SetControlStringValue( selected,
                GetEditorControl(),
                selected->GetDisplayedString() );
        }

        OnValidationFailureReset(selected);

        res = false;

        UnfocusEditor();
    }
    else if ( action == wxPG_ACTION_COPY )
    {


        wxTextCtrl* tc = GetEditorTextCtrl();
        if ( tc )
        {
            wxString sel = tc->GetStringSelection();
            if ( sel.length() )
                CopyTextToClipboard(sel);
        }
        else
        {
            CopyTextToClipboard(selected->GetDisplayedString());
        }
    }
    else if ( action == wxPG_ACTION_CUT )
    {
        wxTextCtrl* tc = GetEditorTextCtrl();
        if ( tc )
        {
            long from, to;
            tc->GetSelection(&from, &to);
            if ( from < to )
            {
                CopyTextToClipboard(tc->GetStringSelection());
                if ( !tc->HasFlag(wxTE_READONLY) )
                    tc->Remove(from, to);
            }
        }
    }
    else if ( action == wxPG_ACTION_PASTE )
    {
        wxTextCtrl* tc = GetEditorTextCtrl();
        if ( tc && !tc->HasFlag(wxTE_READONLY) )
        {
            if (wxTheClipboard->Open())
            {
                if (wxTheClipboard->IsSupported( wxDF_TEXT ))
                {
                    wxTextDataObject data;
                    wxTheClipboard->GetData( data );
                    long from, to;
                    tc->GetSelection(&from, &to);
                    if ( from < to )
                    {
                        tc->Remove(from, to);
                        tc->WriteText(data.GetText());
                    }
                    else
                    {
                        tc->WriteText(data.GetText());
                    }
                }
                wxTheClipboard->Close();
            }
        }
    }
    else if ( action == wxPG_ACTION_SELECT_ALL )
    {
        wxTextCtrl* tc = GetEditorTextCtrl();
        if ( tc )
            tc->SetSelection(-1, -1);
    }

    int keycode = event.GetKeyCode();


    if ( keycode == WXK_PAGEUP || keycode == WXK_PAGEDOWN )
        res = false;

    return res;
}
