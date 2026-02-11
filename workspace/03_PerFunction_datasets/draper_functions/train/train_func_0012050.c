AcpiRsSetResourceLength (
    ACPI_RSDESC_SIZE        TotalLength,
    AML_RESOURCE            *Aml)
{
    ACPI_RS_LENGTH          ResourceLength;


    ACPI_FUNCTION_ENTRY ();


    ResourceLength = (ACPI_RS_LENGTH)
        (TotalLength - AcpiUtGetResourceHeaderLength (Aml));


    if (Aml->SmallHeader.DescriptorType & ACPI_RESOURCE_NAME_LARGE)
    {


        ACPI_MOVE_16_TO_16 (&Aml->LargeHeader.ResourceLength, &ResourceLength);
    }
    else
    {


        Aml->SmallHeader.DescriptorType = (UINT8)


            ((Aml->SmallHeader.DescriptorType & ~ACPI_RESOURCE_NAME_SMALL_LENGTH_MASK)

            | ResourceLength);
    }
}
