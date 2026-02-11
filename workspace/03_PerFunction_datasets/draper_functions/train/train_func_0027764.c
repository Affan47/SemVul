ExecuteOSI (
    char                    *OsiString,
    UINT32                  ExpectedResult)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_LIST        ArgList;
    ACPI_OBJECT             Arg[1];
    ACPI_BUFFER             ReturnValue;
    ACPI_OBJECT             *Obj;


    ArgList.Count = 1;
    ArgList.Pointer = Arg;

    Arg[0].Type = ACPI_TYPE_STRING;
    Arg[0].String.Pointer = OsiString;
    Arg[0].String.Length = strlen (Arg[0].String.Pointer);


    ReturnValue.Length = ACPI_ALLOCATE_BUFFER;

    Status = AcpiEvaluateObject (NULL, "\\_OSI", &ArgList, &ReturnValue);

    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not execute _OSI method, %s\n",
            AcpiFormatException (Status));
        return (Status);
    }

    Status = AE_ERROR;

    if (ReturnValue.Length < sizeof (ACPI_OBJECT))
    {
        AcpiOsPrintf ("Return value from _OSI method too small, %.8X\n",
            ReturnValue.Length);
        goto ErrorExit;
    }

    Obj = ReturnValue.Pointer;
    if (Obj->Type != ACPI_TYPE_INTEGER)
    {
        AcpiOsPrintf ("Invalid return type from _OSI method, %.2X\n", Obj->Type);
        goto ErrorExit;
    }

    if (Obj->Integer.Value != ExpectedResult)
    {
        AcpiOsPrintf ("Invalid return value from _OSI, expected %.8X found %.8X\n",
            ExpectedResult, (UINT32) Obj->Integer.Value);
        goto ErrorExit;
    }

    Status = AE_OK;


    AcpiGbl_OsiData = 0;

ErrorExit:


    AcpiOsFree (ReturnValue.Pointer);

    return (Status);
}
