getlines(std::istream &istr, std::string &line)
{
    if (!istr.good())
        return false;
    line = "";
    int parlevel = 0;
    for (char ch = (char)istr.get(); istr.good(); ch = (char)istr.get())
    {
        if (ch == '\'' || ch == '\"')
        {
            line += ch;
            char c = 0;
            while (istr.good() && c != ch)
            {
                if (c == '\\')
                {
                    c = (char)istr.get();
                    if (!istr.good())
                        return true;
                    line += c;
                }

                c = (char)istr.get();
                if (!istr.good())
                    return true;
                if (c == '\n' && line.compare(0, 1, "#") == 0)
                    return true;
                line += c;
            }
            continue;
        }
        if (ch == '(')
            ++parlevel;
        else if (ch == ')')
            --parlevel;
        else if (ch == '\n')
        {
            if (line.compare(0, 1, "#") == 0)
                return true;

            if (istr.peek() == '#')
            {
                line += ch;
                return true;
            }
        }
        else if (line.compare(0, 1, "#") != 0 && parlevel <= 0 && ch == ';')
        {
            line += ";";
            return true;
        }

        line += ch;
    }
    return true;
}
