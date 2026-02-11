SetupNewDisk()


{
    ULONG Value;

    if (!GetDiskNumber(&MaxDiskSize, GetCurrentDiskNumber(), &Value))
    {
        if (MaxDiskSizeAllSet)
            Value = MaxDiskSizeAll;
        else
            Value = 0;
    }
    SetMaxDiskSize(Value);

    return CAB_STATUS_SUCCESS;
}
