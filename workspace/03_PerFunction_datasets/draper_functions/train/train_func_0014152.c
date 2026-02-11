GetUrl()
    {
        cbStyledTextCtrl* control = m_pOwner->GetControl();
        if (!control)
            return wxEmptyString;

        wxRegEx reUrl(wxT("***:(((ht|f)tp(s?)\\:\\/\\/)|(www\\.))(([a-zA-Z0-9\\-\\._]+(\\.[a-zA-Z0-9\\-\\._]+)+)|localhost)(\\/?)([a-zA-Z0-9\\-\\.\\?\\,\\'\\/\\\\\\+&amp;%\\$#_]*)?([\\d\\w\\.\\/\\%\\+\\-\\=\\&amp;\\?\\:\\\\\\&quot;\\'\\,\\|\\~\\;]*)"));
        wxString url = control->GetSelectedText();

        if (reUrl.Matches(url))
            return reUrl.GetMatch(url);


        int startPos = control->GetCurrentPos();
        const wxString space = wxT(" \n\r\t{}");
        wxChar curCh = control->GetCharAt(startPos);
        while ( (startPos > 0) && (space.Find(curCh) == -1) )
        {
            startPos--;
            curCh = control->GetCharAt(startPos);
        }


        int endPos = control->GetCurrentPos();
        int maxPos = control->GetLineEndPosition(control->GetLineCount());
        curCh = control->GetCharAt(endPos);
        while ( (endPos < maxPos) && (space.Find(curCh) == -1) )
        {
            endPos++;
            curCh = control->GetCharAt(endPos);
        }

        url = control->GetTextRange(startPos, endPos);
        if (    (control->GetLexer() == wxSCI_LEX_CPP)
            &&  (   (control->GetStyleAt(control->GetCurrentPos()) == wxSCI_C_STRING)
                 || (control->GetStyleAt(control->GetCurrentPos()) == wxSCI_C_STRINGEOL) ) )
        {
            url.Replace(wxT("\\n"), wxT("\n"));
            url.Replace(wxT("\\r"), wxT("\r"));
            url.Replace(wxT("\\t"), wxT("\t"));
        }

        if (reUrl.Matches(url))
        {
            wxString match = reUrl.GetMatch(url);
            if (   (url.Find(match) + startPos                       < control->GetCurrentPos())
                && (url.Find(match) + startPos + (int)match.Length() > control->GetCurrentPos()) )
            {
                url = match;
            }
            else
                url = wxEmptyString;
        }
        else
            url = wxEmptyString;

        return url;
    }
