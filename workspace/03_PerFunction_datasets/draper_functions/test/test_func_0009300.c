EatStrConst()
{
    bool isNum = (buffer[0] =='#');
    buffer.clear();
    buffer_low.clear();
    if (isNum)
    {
        EatStrNum();
        if (c == '\'')
            ExtractChar();
        else
            {
                MakeToken(STR_CONST);
                return;
            }
    }
    bool end_of_str = false;
    while (!end_of_str)
    {
        while (!end_of_str)
        {
            if (in.eof())
                Error("end of file in string");
            if (c == '\n') Error("end of line in string");
            if (c != '\'')
            {
                AddToBuffer(c);
                ExtractChar();
            }
            while (c == '\'' && !end_of_str)
            {
                int count;
                for (count = 0; c == '\'' && !in.eof(); ++count, ExtractChar())
                    if (count % 2) AddToBuffer(c);
                if (count % 2) end_of_str = true;
            }
        }
        if (c == '#')
        {
            ExtractChar();
            EatStrNum();
            if (c == '\'')
            {
                ExtractChar();
                end_of_str = false;
            }

        }
    }
    MakeToken(STR_CONST);
}
