getSlotInfo(CK_SLOT_INFO_PTR pSlotInfo)
{
    static CK_VERSION firmwareVersion = {0,0};

    if( pSlotInfo == NULL ) {
        throw PKCS11Exception(CKR_ARGUMENTS_BAD);
    }
    pSlotInfo->flags = CKF_REMOVABLE_DEVICE | CKF_HW_SLOT;

    if( isTokenPresent() )
        pSlotInfo->flags |= CKF_TOKEN_PRESENT;
    memset(pSlotInfo->slotDescription, ' ', 64);
    memcpy(pSlotInfo->slotDescription, readerName,
        MIN(64, strlen(readerName)) );
    memset(pSlotInfo->manufacturerID, ' ', 32);
    memcpy(pSlotInfo->manufacturerID, manufacturer,
        MIN(32, strlen(manufacturer)) );
    pSlotInfo->hardwareVersion = hwVersion;
    pSlotInfo->firmwareVersion = firmwareVersion;

    return CKR_OK;
}
