IsOneOf(wxChar c, const wxChar* chars) const
    {
        while (*chars)
        {
            if (c == *chars)
                return true;
            ++chars;
        }
        return false;
    }
