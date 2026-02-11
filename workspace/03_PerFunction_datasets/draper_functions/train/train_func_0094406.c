AcpiDbUserCommands (
    char                    Prompt,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_STATUS             Status = AE_OK;


    AcpiOsPrintf ("\n");


    while (!AcpiGbl_DbTerminateThreads)
    {


        AcpiDbSetOutputDestination (ACPI_DB_CONSOLE_OUTPUT);


        if (!AcpiGbl_MethodExecuting)
        {
            AcpiOsPrintf ("%1c ", ACPI_DEBUGGER_COMMAND_PROMPT);
        }
        else
        {
            AcpiOsPrintf ("%1c ", ACPI_DEBUGGER_EXECUTE_PROMPT);
        }


        Status = AcpiOsGetLine (AcpiGbl_DbLineBuf,
            ACPI_DB_LINE_BUFFER_SIZE, NULL);
        if (ACPI_FAILURE (Status))
        {
            ACPI_EXCEPTION ((AE_INFO, Status, "While parsing command line"));
            return (Status);
        }


        if (AcpiGbl_DebuggerConfiguration & DEBUGGER_MULTI_THREADED)
        {


            Status = AcpiUtReleaseMutex (ACPI_MTX_DEBUG_CMD_READY);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }

            Status = AcpiUtAcquireMutex (ACPI_MTX_DEBUG_CMD_COMPLETE);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }
        }
        else
        {


            AcpiDbSingleThread ();
        }
    }


    Status = AcpiTerminate ();
    return (Status);
}
