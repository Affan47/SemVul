EatBlockComment()
{
    if (c == '{')
    {
        do {
            ExtractChar();
            if (c == '\n')
            {
                ++line;
                pos = 0;
            }
            if (in.eof()) Error("end of file in comment");
        } while (c != '}');
        ExtractChar();
    }
}
