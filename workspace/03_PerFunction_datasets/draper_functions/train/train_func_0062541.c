AcpiDbGetFromHistory (
    char                    *CommandNumArg)
{
    UINT32                  CmdNum;


    if (CommandNumArg == NULL)
    {
        CmdNum = AcpiGbl_NextCmdNum - 1;
    }

    else
    {
        CmdNum = ACPI_STRTOUL (CommandNumArg, NULL, 0);
    }

    return (AcpiDbGetHistoryByIndex (CmdNum));
}
