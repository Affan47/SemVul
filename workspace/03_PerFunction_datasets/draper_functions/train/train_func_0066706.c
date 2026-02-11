AcpiDmDumpSerialBusVendorData (
    AML_RESOURCE            *Resource,
    UINT32                  Level)
{
    UINT8                   *VendorData;
    UINT32                  VendorLength;


    switch (Resource->CommonSerialBus.Type)
    {
    case AML_RESOURCE_I2C_SERIALBUSTYPE:

        VendorLength = Resource->CommonSerialBus.TypeDataLength -
            AML_RESOURCE_I2C_MIN_DATA_LEN;

        VendorData = ACPI_ADD_PTR (UINT8, Resource,
            sizeof (AML_RESOURCE_I2C_SERIALBUS));
        break;

    case AML_RESOURCE_SPI_SERIALBUSTYPE:

        VendorLength = Resource->CommonSerialBus.TypeDataLength -
            AML_RESOURCE_SPI_MIN_DATA_LEN;

        VendorData = ACPI_ADD_PTR (UINT8, Resource,
            sizeof (AML_RESOURCE_SPI_SERIALBUS));
        break;

    case AML_RESOURCE_UART_SERIALBUSTYPE:

        VendorLength = Resource->CommonSerialBus.TypeDataLength -
            AML_RESOURCE_UART_MIN_DATA_LEN;

        VendorData = ACPI_ADD_PTR (UINT8, Resource,
            sizeof (AML_RESOURCE_UART_SERIALBUS));
        break;

    default:

        return;
    }


    AcpiDmDumpRawDataBuffer (VendorData, VendorLength, Level);
}
