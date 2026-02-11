AcpiRsDumpResourceList (
    ACPI_RESOURCE           *ResourceList)
{
    UINT32                  Count = 0;
    UINT32                  Type;


    ACPI_FUNCTION_ENTRY ();


    if (!ACPI_IS_DEBUG_ENABLED (ACPI_LV_RESOURCES, _COMPONENT))
    {
        return;
    }


    do
    {
        AcpiOsPrintf ("\n[%02X] ", Count);
        Count++;


        Type = ResourceList->Type;
        if (Type > ACPI_RESOURCE_TYPE_MAX)
        {
            AcpiOsPrintf (
                "Invalid descriptor type (%X) in resource list\n",
                ResourceList->Type);
            return;
        }


        if (!ResourceList->Length)
        {
            AcpiOsPrintf (
                "Invalid zero length descriptor in resource list\n");
            return;
        }


        if (Type == ACPI_RESOURCE_TYPE_SERIAL_BUS)
        {
            AcpiRsDumpDescriptor (&ResourceList->Data,
                AcpiGbl_DumpSerialBusDispatch[ResourceList->Data.CommonSerialBus.Type]);
        }
        else
        {
            AcpiRsDumpDescriptor (&ResourceList->Data,
                AcpiGbl_DumpResourceDispatch[Type]);
        }


        ResourceList = ACPI_NEXT_RESOURCE (ResourceList);


    } while (Type != ACPI_RESOURCE_TYPE_END_TAG);
}
