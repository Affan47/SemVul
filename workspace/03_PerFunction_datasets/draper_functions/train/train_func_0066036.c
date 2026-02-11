LsWriteSourceLines (
    UINT32                  ToLineNumber,
    UINT32                  ToLogicalLineNumber,
    UINT32                  FileId)
{


    if ((FileId == ASL_FILE_ASM_INCLUDE_OUTPUT) ||
        (FileId == ASL_FILE_C_INCLUDE_OUTPUT))
    {
        return;
    }

    Gbl_CurrentLine = ToLogicalLineNumber;


    LsFlushListingBuffer (FileId);


    if (Gbl_SourceLine < Gbl_CurrentLine)
    {


        if (Gbl_HexBytesWereWritten)
        {
            FlPrintFile (FileId, "\n");
            Gbl_HexBytesWereWritten = FALSE;
        }

        if (FileId == ASL_FILE_C_SOURCE_OUTPUT)
        {
            FlPrintFile (FileId, "    /*\n");
        }


        while ((Gbl_SourceLine < Gbl_CurrentLine) &&
                LsWriteOneSourceLine (FileId))
        { ; }

        if (FileId == ASL_FILE_C_SOURCE_OUTPUT)
        {
            FlPrintFile (FileId, "     */");
        }

        FlPrintFile (FileId, "\n");
    }
}
