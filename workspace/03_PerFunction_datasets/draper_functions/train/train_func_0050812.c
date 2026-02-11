AsRemoveEmptyBlocks (
    char                    *Buffer,
    char                    *Filename)
{
    char                    *SubBuffer;
    char                    *BlockStart;
    BOOLEAN                 EmptyBlock = TRUE;
    BOOLEAN                 AnotherPassRequired = TRUE;
    UINT32                  BlockCount = 0;


    while (AnotherPassRequired)
    {
        SubBuffer = Buffer;
        AnotherPassRequired = FALSE;

        while (*SubBuffer)
        {
            if (*SubBuffer == '{')
            {
                BlockStart = SubBuffer;
                EmptyBlock = TRUE;

                SubBuffer++;
                while (*SubBuffer != '}')
                {
                    if ((*SubBuffer != ' ') &&
                        (*SubBuffer != '\n'))
                    {
                        EmptyBlock = FALSE;
                        break;
                    }
                    SubBuffer++;
                }

                if (EmptyBlock)
                {


                    while (*BlockStart != '\n')
                    {
                        BlockStart--;
                    }


                    SubBuffer = AsSkipUntilChar (SubBuffer, '\n');
                    if (!SubBuffer)
                    {
                        break;
                    }


                    SubBuffer = AsRemoveData (BlockStart, SubBuffer);
                    BlockCount++;
                    AnotherPassRequired = TRUE;
                    continue;
                }
            }

            SubBuffer++;
        }
    }

    if (BlockCount)
    {
        Gbl_MadeChanges = TRUE;
        AsPrint ("Code blocks deleted", BlockCount, Filename);
    }
}
