AcpiDbDumpNamespaceByOwner (
    char                    *OwnerArg,
    char                    *DepthArg)
{
    ACPI_HANDLE             SubtreeEntry = AcpiGbl_RootNode;
    UINT32                  MaxDepth = ACPI_UINT32_MAX;
    ACPI_OWNER_ID           OwnerId;


    OwnerId = (ACPI_OWNER_ID) ACPI_STRTOUL (OwnerArg, NULL, 0);


    if (DepthArg)
    {
        MaxDepth = ACPI_STRTOUL (DepthArg, NULL, 0);
    }

    AcpiDbSetOutputDestination (ACPI_DB_DUPLICATE_OUTPUT);
    AcpiOsPrintf ("ACPI Namespace by owner %X:\n", OwnerId);


    AcpiDbSetOutputDestination (ACPI_DB_REDIRECTABLE_OUTPUT);
    AcpiNsDumpObjects (ACPI_TYPE_ANY, ACPI_DISPLAY_SUMMARY, MaxDepth, OwnerId,
        SubtreeEntry);
    AcpiDbSetOutputDestination (ACPI_DB_CONSOLE_OUTPUT);
}
