FlConsumeAnsiComment (
    FILE                    *Handle,
    ASL_FILE_STATUS         *Status)
{
    UINT8                   Byte;
    BOOLEAN                 ClosingComment = FALSE;


    while (fread (&Byte, 1, 1, Handle) == 1)
    {


        if (ClosingComment)
        {
            if (Byte == '/')
            {
                return;
            }

            if (Byte != '*')
            {


                ClosingComment = FALSE;
            }
        }
        else if (Byte == '*')
        {
            ClosingComment = TRUE;
        }


        if (Byte == 0x0A)
        {
            Status->Line++;
        }

        Status->Offset++;
    }
}
