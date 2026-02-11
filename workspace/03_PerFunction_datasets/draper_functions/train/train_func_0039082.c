AcpiDbExecute (
    char                    *Name,
    char                    **Args,
    ACPI_OBJECT_TYPE        *Types,
    UINT32                  Flags)
{
    ACPI_STATUS             Status;
    ACPI_BUFFER             ReturnObj;
    char                    *NameString;


#ifdef ACPI_DEBUG_OUTPUT
    UINT32                  PreviousAllocations;
    UINT32                  Allocations;


    PreviousAllocations = AcpiDbGetOutstandingAllocations ();
#endif

    if (*Name == '*')
    {
        (void) AcpiWalkNamespace (ACPI_TYPE_METHOD, ACPI_ROOT_OBJECT,
                    ACPI_UINT32_MAX, AcpiDbExecutionWalk, NULL, NULL, NULL);
        return;
    }
    else
    {
        NameString = ACPI_ALLOCATE (ACPI_STRLEN (Name) + 1);
        if (!NameString)
        {
            return;
        }

        ACPI_MEMSET (&AcpiGbl_DbMethodInfo, 0, sizeof (ACPI_DB_METHOD_INFO));

        ACPI_STRCPY (NameString, Name);
        AcpiUtStrupr (NameString);
        AcpiGbl_DbMethodInfo.Name = NameString;
        AcpiGbl_DbMethodInfo.Args = Args;
        AcpiGbl_DbMethodInfo.Types = Types;
        AcpiGbl_DbMethodInfo.Flags = Flags;

        ReturnObj.Pointer = NULL;
        ReturnObj.Length = ACPI_ALLOCATE_BUFFER;

        Status = AcpiDbExecuteSetup (&AcpiGbl_DbMethodInfo);
        if (ACPI_FAILURE (Status))
        {
            ACPI_FREE (NameString);
            return;
        }


        Status = AcpiGetHandle (NULL, AcpiGbl_DbMethodInfo.Pathname,
            &AcpiGbl_DbMethodInfo.Method);
        if (ACPI_SUCCESS (Status))
        {
            Status = AcpiDbExecuteMethod (&AcpiGbl_DbMethodInfo, &ReturnObj);
        }
        ACPI_FREE (NameString);
    }


    AcpiOsSleep ((UINT64) 10);

#ifdef ACPI_DEBUG_OUTPUT


    Allocations = AcpiDbGetOutstandingAllocations () - PreviousAllocations;

    AcpiDbSetOutputDestination (ACPI_DB_DUPLICATE_OUTPUT);

    if (Allocations > 0)
    {
        AcpiOsPrintf ("0x%X Outstanding allocations after evaluation of %s\n",
                        Allocations, AcpiGbl_DbMethodInfo.Pathname);
    }
#endif

    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Evaluation of %s failed with status %s\n",
            AcpiGbl_DbMethodInfo.Pathname, AcpiFormatException (Status));
    }
    else
    {


        if (ReturnObj.Length)
        {
            AcpiOsPrintf (
                "Evaluation of %s returned object %p, external buffer length %X\n",
                AcpiGbl_DbMethodInfo.Pathname, ReturnObj.Pointer,
                (UINT32) ReturnObj.Length);
            AcpiDbDumpExternalObject (ReturnObj.Pointer, 1);


            if (ACPI_COMPARE_NAME ((ACPI_CAST_PTR (ACPI_NAMESPACE_NODE,
                    AcpiGbl_DbMethodInfo.Method)->Name.Ascii), METHOD_NAME__PLD))
            {
                AcpiDbDumpPldBuffer (ReturnObj.Pointer);
            }
        }
        else
        {
            AcpiOsPrintf ("No object was returned from evaluation of %s\n",
                AcpiGbl_DbMethodInfo.Pathname);
        }
    }

    AcpiDbSetOutputDestination (ACPI_DB_CONSOLE_OUTPUT);
}
