AcpiRsDumpResourceSource (
    ACPI_RESOURCE_SOURCE    *ResourceSource)
{
    ACPI_FUNCTION_ENTRY ();


    if (ResourceSource->Index == 0xFF)
    {
        return;
    }

    AcpiRsOutInteger8 ("Resource Source Index",
        ResourceSource->Index);

    AcpiRsOutString ("Resource Source",
        ResourceSource->StringPtr ?
            ResourceSource->StringPtr : "[Not Specified]");
}
