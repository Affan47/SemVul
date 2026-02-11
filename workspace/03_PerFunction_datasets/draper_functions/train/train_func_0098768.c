wrapText(const wxString& text, size_t maxWidth, size_t indent)
{
    wxString indentStr;
    bool eol(false);
    wxString wrappedText;
    wxString line;

    wxString::const_iterator lastSpace = text.end();
    wxString::const_iterator lineStart = text.begin();
    for (wxString::const_iterator it = lineStart; ; ++it)
    {
        if (eol)
        {
            wrappedText += wxT('\n');
            if (indentStr.IsEmpty())
                indentStr.Pad(indent);

            lastSpace = text.end();
            line.clear();
            lineStart = it;
        }
        eol = false;

        if (it == text.end() || *it == wxT('\n'))
        {
            wrappedText << indentStr << line;
            eol = true;
            if (it == text.end())
                break;
        }
        else
        {
            if (*it == wxT(' '))
                lastSpace = it;

            line += *it;

            if (maxWidth >= 0 && lastSpace != text.end())
            {
                size_t width = line.Length();
                if (width > maxWidth - indentStr.Length())
                {

                    line.erase(lastSpace - lineStart, it + 1 - lineStart);
                    wrappedText << indentStr << line;
                    eol = true;


                    it = lastSpace;
                }
            }

        }
    }
    return wrappedText;
}
