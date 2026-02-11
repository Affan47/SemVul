AcpiUtRemoveInterface (
    ACPI_STRING             InterfaceName)
{
    ACPI_INTERFACE_INFO     *PreviousInterface;
    ACPI_INTERFACE_INFO     *NextInterface;


    PreviousInterface = NextInterface = AcpiGbl_SupportedInterfaces;
    while (NextInterface)
    {
        if (!ACPI_STRCMP (InterfaceName, NextInterface->Name))
        {


            if (NextInterface->Flags & ACPI_OSI_DYNAMIC)
            {


                if (PreviousInterface == NextInterface)
                {
                    AcpiGbl_SupportedInterfaces = NextInterface->Next;
                }
                else
                {
                    PreviousInterface->Next = NextInterface->Next;
                }

                ACPI_FREE (NextInterface->Name);
                ACPI_FREE (NextInterface);
            }
            else
            {


                if (NextInterface->Flags & ACPI_OSI_INVALID)
                {
                    return (AE_NOT_EXIST);
                }

                NextInterface->Flags |= ACPI_OSI_INVALID;
            }

            return (AE_OK);
        }

        PreviousInterface = NextInterface;
        NextInterface = NextInterface->Next;
    }


    return (AE_NOT_EXIST);
}
