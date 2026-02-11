nssCKFWSession_Update
(
  NSSCKFWSession *fwSession,
  NSSCKFWCryptoOperationType type,
  NSSCKFWCryptoOperationState state,
  CK_BYTE_PTR  inBuf,
  CK_ULONG     inBufLen,
  CK_BYTE_PTR  outBuf,
  CK_ULONG_PTR outBufLen
)
{
  NSSCKFWCryptoOperation *fwOperation;
  NSSItem inputBuffer;
  NSSItem outputBuffer;
  CK_ULONG len;
  CK_ULONG maxBufLen;
  CK_RV error = CKR_OK;

#ifdef NSSDEBUG
  error = nssCKFWSession_verifyPointer(fwSession);
  if( CKR_OK != error ) {
    return error;
  }

  if (!fwSession->mdSession) {
    return CKR_GENERAL_ERROR;
  }
#endif


  fwOperation = nssCKFWSession_GetCurrentCryptoOperation(fwSession, state);
  if (!fwOperation) {
    return CKR_OPERATION_NOT_INITIALIZED;
  }


  if (type != nssCKFWCryptoOperation_GetType(fwOperation)) {
    return CKR_OPERATION_NOT_INITIALIZED;
  }

  inputBuffer.data = inBuf;
  inputBuffer.size = inBufLen;


  len = nssCKFWCryptoOperation_GetOperationLength(fwOperation, &inputBuffer,
                                                  &error);
  if (CKR_OK != error) {
    return error;
  }
  maxBufLen = *outBufLen;

  *outBufLen = len;
  if ((CK_BYTE_PTR)NULL == outBuf) {
    return CKR_OK;
  }

  if (len > maxBufLen) {
    return CKR_BUFFER_TOO_SMALL;
  }
  outputBuffer.data = outBuf;
  outputBuffer.size = *outBufLen;

  return nssCKFWCryptoOperation_Update(fwOperation,
                                       &inputBuffer, &outputBuffer);
}
