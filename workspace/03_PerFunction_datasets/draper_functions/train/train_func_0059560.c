AsRemoveConditionalCompile (
    char                    *Buffer,
    char                    *Keyword)
{
    char                    *SubString;
    char                    *SubBuffer;
    char                    *IfPtr;
    char                    *EndifPtr;
    char                    *ElsePtr;
    char                    *Comment;
    int                     KeywordLength;


    KeywordLength = strlen (Keyword);
    SubBuffer = Buffer;
    SubString = Buffer;


    while (SubString)
    {
        SubBuffer = strstr (SubString, Keyword);
        if (!SubBuffer)
        {
            return;
        }


        if (Gbl_IgnoreTranslationEscapes)
        {
            Comment = NULL;
        }
        else
        {
            Comment = strstr (SubString, AS_START_IGNORE);
        }

        if ((Comment) &&
            (Comment < SubBuffer))
        {
            SubString = strstr (Comment, AS_STOP_IGNORE);
            if (!SubString)
            {
                return;
            }

            SubString += 3;
            continue;
        }


        Comment = strstr (SubString, "/*");

        if ((Comment) &&
            (Comment < SubBuffer))
        {
            SubString = strstr (Comment, "*/");
            if (!SubString)
            {
                return;
            }

            SubString += 2;
            continue;
        }

        SubString = SubBuffer;
        if (!AsMatchExactWord (SubString, KeywordLength))
        {
            SubString++;
            continue;
        }


        while (*SubString != '\n' && (SubString > Buffer))
        {
            SubString--;
        }
        SubString++;


        IfPtr = strstr (SubString, "#if");
        if (!IfPtr)
        {
            return;
        }

        if (IfPtr > SubBuffer)
        {


            SubString = SubBuffer + strlen (Keyword);
            continue;
        }


        EndifPtr = strstr (SubBuffer, "#endif");
        if (!EndifPtr)
        {


            return;
        }

        ElsePtr = strstr (SubBuffer, "#else");
        if ((ElsePtr) &&
            (EndifPtr > ElsePtr))
        {


            SubBuffer = AsSkipPastChar (ElsePtr, '\n');
            if (!SubBuffer)
            {
                return;
            }


            AsRemoveData (SubString, SubBuffer);


            EndifPtr = strstr (SubString, "#endif");
            if (!EndifPtr)
            {


                return;
            }

            SubString = EndifPtr;
        }


        SubBuffer = AsSkipPastChar (EndifPtr, '\n');
        if (!SubBuffer)
        {
            return;
        }


        SubBuffer = AsRemoveData (SubString, SubBuffer);
    }
}
