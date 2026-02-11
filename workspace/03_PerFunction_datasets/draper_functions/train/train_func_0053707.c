AcpiHwBuildPciList (
    ACPI_HANDLE             RootPciDevice,
    ACPI_HANDLE             PciRegion,
    ACPI_PCI_DEVICE         **ReturnListHead)
{
    ACPI_HANDLE             CurrentDevice;
    ACPI_HANDLE             ParentDevice;
    ACPI_STATUS             Status;
    ACPI_PCI_DEVICE         *ListElement;
    ACPI_PCI_DEVICE         *ListHead = NULL;


    CurrentDevice = PciRegion;
    while (1)
    {
        Status = AcpiGetParent (CurrentDevice, &ParentDevice);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }


        if (ParentDevice == RootPciDevice)
        {
            *ReturnListHead = ListHead;
            return (AE_OK);
        }

        ListElement = ACPI_ALLOCATE (sizeof (ACPI_PCI_DEVICE));
        if (!ListElement)
        {
            return (AE_NO_MEMORY);
        }


        ListElement->Next = ListHead;
        ListElement->Device = ParentDevice;
        ListHead = ListElement;

        CurrentDevice = ParentDevice;
    }
}
