AsCountSourceLines (
    char                    *Buffer,
    char                    *Filename)
{
    char                    *SubBuffer = Buffer;
    UINT32                  LineCount = 0;
    UINT32                  WhiteCount = 0;
    UINT32                  CommentCount = 0;


    while (*SubBuffer)
    {


        if ((SubBuffer[0] == '/') &&
            (SubBuffer[1] == '*'))
        {
            SubBuffer += 2;


            if (SubBuffer[0] == '\n')
            {
                WhiteCount++;
                SubBuffer++;
            }
            else
            {
                CommentCount++;
            }


            while (SubBuffer[0] && SubBuffer[1] &&
                    !(((SubBuffer[0] == '*') &&
                      (SubBuffer[1] == '/'))))
            {
                if (SubBuffer[0] == '\n')
                {
                    CommentCount++;
                }

                SubBuffer++;
            }
        }


        else if ((SubBuffer[0] == '\n') &&
                 (SubBuffer[1] != '\n'))
        {
            LineCount++;
        }


        else if ((SubBuffer[0] == '\n') &&
                 (SubBuffer[1] == '\n'))
        {
            WhiteCount++;
        }

        SubBuffer++;
    }


    if (Gbl_HeaderSize < CommentCount)
    {
        CommentCount -= Gbl_HeaderSize;
        Gbl_HeaderLines += Gbl_HeaderSize;
    }

    Gbl_SourceLines += LineCount;
    Gbl_WhiteLines += WhiteCount;
    Gbl_CommentLines += CommentCount;

    VERBOSE_PRINT (("%u Comment %u White %u Code %u Lines in %s\n",
                CommentCount, WhiteCount, LineCount, LineCount+WhiteCount+CommentCount, Filename));
}
