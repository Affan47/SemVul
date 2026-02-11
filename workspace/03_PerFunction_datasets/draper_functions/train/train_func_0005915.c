state_cl_httpresulttext(char ch)
    {
        if (ch == '\r')
        {
            ev.onHttpReturn(value, token);
            state = &HeaderParser::state_cl_httpresult_cr;
            return;
        }
        else if (ch == '\n')
        {
            ev.onHttpReturn(value, token);
            state = &HeaderParser::state_h0;
            return;
        }
        else if (token.empty() && (ch == ' ' || ch == '\t'))
        {
            return;
        }
        else
        {
            token += ch;
            return;
        }
    }
