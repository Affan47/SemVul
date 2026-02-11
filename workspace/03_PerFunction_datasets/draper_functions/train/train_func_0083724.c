NSSCKFWC_GetSlotInfo
(
  NSSCKFWInstance *fwInstance,
  CK_SLOT_ID slotID,
  CK_SLOT_INFO_PTR pInfo
)
{
  CK_RV error = CKR_OK;
  CK_ULONG nSlots;
  NSSCKFWSlot **slots;
  NSSCKFWSlot *fwSlot;

  if (!fwInstance) {
    error = CKR_CRYPTOKI_NOT_INITIALIZED;
    goto loser;
  }

  nSlots = nssCKFWInstance_GetNSlots(fwInstance, &error);
  if( (CK_ULONG)0 == nSlots ) {
    goto loser;
  }

  if( (slotID < 1) || (slotID > nSlots) ) {
    error = CKR_SLOT_ID_INVALID;
    goto loser;
  }

  if( (CK_SLOT_INFO_PTR)CK_NULL_PTR == pInfo ) {
    error = CKR_ARGUMENTS_BAD;
    goto loser;
  }


  (void)nsslibc_memset(pInfo, 0, sizeof(CK_SLOT_INFO));

  slots = nssCKFWInstance_GetSlots(fwInstance, &error);
  if( (NSSCKFWSlot **)NULL == slots ) {
    goto loser;
  }

  fwSlot = slots[ slotID-1 ];

  error = nssCKFWSlot_GetSlotDescription(fwSlot, pInfo->slotDescription);
  if( CKR_OK != error ) {
    goto loser;
  }

  error = nssCKFWSlot_GetManufacturerID(fwSlot, pInfo->manufacturerID);
  if( CKR_OK != error ) {
    goto loser;
  }

  if( nssCKFWSlot_GetTokenPresent(fwSlot) ) {
    pInfo->flags |= CKF_TOKEN_PRESENT;
  }

  if( nssCKFWSlot_GetRemovableDevice(fwSlot) ) {
    pInfo->flags |= CKF_REMOVABLE_DEVICE;
  }

  if( nssCKFWSlot_GetHardwareSlot(fwSlot) ) {
    pInfo->flags |= CKF_HW_SLOT;
  }

  pInfo->hardwareVersion = nssCKFWSlot_GetHardwareVersion(fwSlot);
  pInfo->firmwareVersion = nssCKFWSlot_GetFirmwareVersion(fwSlot);

  return CKR_OK;

 loser:
  switch( error ) {
  case CKR_CRYPTOKI_NOT_INITIALIZED:
  case CKR_DEVICE_ERROR:
  case CKR_FUNCTION_FAILED:
  case CKR_GENERAL_ERROR:
  case CKR_HOST_MEMORY:
  case CKR_SLOT_ID_INVALID:
    break;
  default:
  case CKR_OK:
    error = CKR_GENERAL_ERROR;
  }

  return error;
}
