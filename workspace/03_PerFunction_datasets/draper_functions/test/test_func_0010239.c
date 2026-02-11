LibDuplicateDevicePathInstance (
    IN EFI_DEVICE_PATH  *DevPath
    )
{
    EFI_DEVICE_PATH     *NewDevPath,*DevicePathInst,*Temp;
    UINTN               Size;


    Temp = DevPath;
    DevicePathInst = DevicePathInstance (&Temp, &Size);


    NewDevPath = NULL;
    if (Size) {
        NewDevPath = AllocatePool (Size + sizeof(EFI_DEVICE_PATH));
    }

    if (NewDevPath) {
        CopyMem (NewDevPath, DevicePathInst, Size);
        Temp = NextDevicePathNode(NewDevPath);
        SetDevicePathEndNode(Temp);
    }

    return NewDevPath;
}
