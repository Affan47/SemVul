CheckCrcAltSize (
    IN UINTN                 MaxSize,
    IN UINTN                 Size,
    IN OUT EFI_TABLE_HEADER *Hdr
    )


{
    UINT32      Crc;
    UINT32      OrgCrc;
    BOOLEAN     f;

    if (Size == 0) {


        return FALSE;
    }
    if (MaxSize && Size > MaxSize) {
        DEBUG((D_ERROR, "CheckCrc32: Size > MaxSize\n"));
        return FALSE;
    }


    OrgCrc = Hdr->CRC32;
    Hdr->CRC32 = 0;
    Crc = CalculateCrc((UINT8 *)Hdr, Size);


    Hdr->CRC32 = OrgCrc;


    f = OrgCrc == (UINT32) Crc;
    if (!f) {
        DEBUG((D_ERROR, "CheckCrc32: Crc check failed\n"));
    }

    return f;
}
