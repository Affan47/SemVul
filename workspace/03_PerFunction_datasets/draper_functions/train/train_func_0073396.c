DtDoCompile (
    void)
{
    ACPI_STATUS             Status;
    UINT8                   Event;
    DT_FIELD                *FieldList;


    Status = DtInitialize ();
    if (ACPI_FAILURE (Status))
    {
        printf ("Error during compiler initialization, 0x%X\n", Status);
        return (Status);
    }


    Event = UtBeginEvent ("Preprocess input file");
    PrDoPreprocess ();
    UtEndEvent (Event);

    if (Gbl_PreprocessOnly)
    {
        return (AE_OK);
    }


    Event = UtBeginEvent ("Scan and parse input file");
    FieldList = DtScanFile (Gbl_Files[ASL_FILE_INPUT].Handle);
    UtEndEvent (Event);


    if (!FieldList)
    {


        DtError (ASL_ERROR, ASL_MSG_SYNTAX, NULL,
            "Input file does not appear to be an ASL or data table source file");

        Status = AE_ERROR;
        goto CleanupAndExit;
    }

    Event = UtBeginEvent ("Compile parse tree");


    Status = DtCompileDataTable (&FieldList);
    UtEndEvent (Event);

    DtFreeFieldList ();

    if (ACPI_FAILURE (Status))
    {


        DtError (ASL_ERROR, ASL_MSG_SYNTAX, NULL,
            "Could not compile input file");

        goto CleanupAndExit;
    }


    Gbl_Files[ASL_FILE_AML_OUTPUT].Filename = NULL;
    Status = FlOpenAmlOutputFile (Gbl_OutputFilenamePrefix);
    if (ACPI_FAILURE (Status))
    {
        goto CleanupAndExit;
    }


    DtOutputBinary (Gbl_RootTable);
    HxDoHexOutput ();
    DtWriteTableToListing ();

CleanupAndExit:

    CmCleanupAndExit ();
    return (Status);
}
