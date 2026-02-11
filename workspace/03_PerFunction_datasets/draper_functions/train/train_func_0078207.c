AhDisplayDeviceIds (
    void)
{
    const AH_DEVICE_ID      *DeviceId = AhDeviceIds;


    printf ("ACPI and PNP Device IDs defined in the ACPI specification:\n\n");
    while (DeviceId->Name)
    {
        printf ("%8s   %s\n", DeviceId->Name, DeviceId->Description);
        DeviceId++;
    }
}
