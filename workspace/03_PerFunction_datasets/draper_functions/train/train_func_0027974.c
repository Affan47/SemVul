_DevPathVendor (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    VENDOR_DEVICE_PATH                  *Vendor;
    CHAR16                              *Type;
    UNKNOWN_DEVICE_VENDOR_DEVICE_PATH   *UnknownDevPath;

    Vendor = DevPath;
    switch (DevicePathType(&Vendor->Header)) {
    case HARDWARE_DEVICE_PATH:  Type = L"Hw";        break;
    case MESSAGING_DEVICE_PATH: Type = L"Msg";       break;
    case MEDIA_DEVICE_PATH:     Type = L"Media";     break;
    default:                    Type = L"?";         break;
    }

    CatPrint(Str, L"Ven%s(%g", Type, &Vendor->Guid);
    if (CompareGuid (&Vendor->Guid, &UnknownDevice) == 0) {


        UnknownDevPath = (UNKNOWN_DEVICE_VENDOR_DEVICE_PATH *)Vendor;
        CatPrint(Str, L":%02x)", UnknownDevPath->LegacyDriveLetter);
    } else {
        CatPrint(Str, L")");
    }
}
