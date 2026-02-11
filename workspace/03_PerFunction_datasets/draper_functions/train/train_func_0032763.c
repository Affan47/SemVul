AsCheckAndSkipLiterals (
    char                    *Buffer,
    UINT32                  *TotalLines)
{
    UINT32                  NewLines = 0;
    char                    *SubBuffer = Buffer;
    char                    *LiteralEnd;


    if ((SubBuffer[0] == '/') &&
        (SubBuffer[1] == '*'))
    {
        LiteralEnd = strstr (SubBuffer, "*/");
        SubBuffer += 2;

        if (!LiteralEnd)
        {
            return (SubBuffer);
        }

        while (SubBuffer < LiteralEnd)
        {
            if (*SubBuffer == '\n')
            {
                NewLines++;
            }

            SubBuffer++;
        }

        SubBuffer += 2;
    }


    else if (*SubBuffer == '\"')
    {
        SubBuffer++;
        LiteralEnd = AsSkipPastChar (SubBuffer, '\"');
        if (!LiteralEnd)
        {
            return (SubBuffer);
        }
    }

    if (TotalLines)
    {
        (*TotalLines) += NewLines;
    }
    return (SubBuffer);
}
