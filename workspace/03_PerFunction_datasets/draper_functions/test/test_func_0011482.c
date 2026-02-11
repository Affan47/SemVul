DevicePathSize (
    IN EFI_DEVICE_PATH  *DevPath
    )
{
    EFI_DEVICE_PATH     *Start;


    Start = DevPath;
    while (!IsDevicePathEnd(DevPath)) {
        DevPath = NextDevicePathNode(DevPath);
    }


    return ((UINTN) DevPath - (UINTN) Start) + sizeof(EFI_DEVICE_PATH);
}
