processElementAttributes(void)
{
    bool loop = TRUE;
    char current = getNextChar();
    if (isWhite(current))
    {
        printError("processElementAttributes : first char shouldn't be a white");
        result = PRETTY_PRINTING_INVALID_CHAR_ERROR;
        return;
    }

    while (loop)
    {
        char next;

        readWhites(TRUE);

        next = getNextChar();
        if (next == '/') { loop = FALSE; }
        else if (next == '>') { loop = FALSE; }
        else if (next == '?') { loop = FALSE; }
        else
        {
            putCharInBuffer(' ');
            processElementAttribute();
        }
    }
}
