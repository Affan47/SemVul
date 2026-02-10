processComment(void)
{
    char lastChar;
    bool loop = TRUE;
    char oldChar;
    bool inlineAllowed = FALSE;
    if (options->inlineComment) { inlineAllowed = isInlineNodeAllowed(); }
    if (inlineAllowed && !options->oneLineComment) { inlineAllowed = isOnSingleLine(4, '-', '-'); }
    if (inlineAllowed) { resetBackwardIndentation(TRUE); }

    putNextCharsInBuffer(4);

    oldChar = '-';
    while (loop)
    {
        char nextChar = readNextChar();
        if (oldChar == '-' && nextChar == '-')
        {
            loop = FALSE;
        }

        if (!isLineBreak(nextChar))
        {
            if (options->oneLineComment && isSpace(nextChar))
            {

                while(isSpace(getNextChar()))
                {
                    nextChar = readNextChar();
                }
                putCharInBuffer(' ');
                oldChar = ' ';
            }
            else
            {

                putCharInBuffer(nextChar);
                oldChar = nextChar;
            }

            if (!loop && options->alignComment)
            {


                bool onlySpaces = xmlPrettyPrinted[xmlPrettyPrintedIndex-3] == ' ' &&
                                  xmlPrettyPrinted[xmlPrettyPrintedIndex-4] == ' ' &&
                                  xmlPrettyPrinted[xmlPrettyPrintedIndex-5] == ' ' &&
                                  xmlPrettyPrinted[xmlPrettyPrintedIndex-6] == ' ' &&
                                  xmlPrettyPrinted[xmlPrettyPrintedIndex-7] == ' ';


                if (onlySpaces)
                {
                    xmlPrettyPrintedIndex -= 7;
                    putCharsInBuffer("--");
                }
            }
        }
        else if (!options->oneLineComment && !inlineAllowed)
        {

            if (options->alignComment)
            {
                int read = readWhites(FALSE);
                if (nextChar == '\r' && read == 0 && getNextChar() == '\n')
                {
                    readNextChar();
                    readWhites(FALSE);
                }

                putNewLine();
                putCharsInBuffer("     ");
                oldChar = ' ';
            }
            else
            {
                putCharInBuffer(nextChar);
                oldChar = nextChar;
            }
        }
        else
        {
            readWhites(TRUE);
            if (getPreviousInsertedChar() != ' ' &&
                strncmp(xmlPrettyPrinted+xmlPrettyPrintedIndex-4, "<!--", 4) != 0)
            {
                putCharInBuffer(' ');
                oldChar = ' ';
            }
        }
    }

    lastChar = readNextChar();
    if (lastChar != '>')
    {
        printError("processComment : last char must be '>' (not '%c')", lastChar);
        result = PRETTY_PRINTING_INVALID_CHAR_ERROR;
        return;
    }
    putCharInBuffer(lastChar);

    if (inlineAllowed) { appendIndentation = FALSE; }


    lastNodeOpen = FALSE;
}
