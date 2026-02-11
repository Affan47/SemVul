GetLineIndentString(int line, cbStyledTextCtrl* stc)
    {
        int currLine = (line == -1)
                        ? stc->LineFromPosition(stc->GetCurrentPos())
                        : line;
        wxString text = stc->GetLine(currLine);
        unsigned int len = text.Length();
        wxString indent;
        for (unsigned int i = 0; i < len; ++i)
        {
            if (text[i] == _T(' ') || text[i] == _T('\t'))
            {
                indent << text[i];
            }
            else
            {
                break;
            }
        }
        return indent;
    }
