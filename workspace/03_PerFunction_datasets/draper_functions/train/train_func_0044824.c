DIMSE_moveProvider(

    T_ASC_Association *assoc,
    T_ASC_PresentationContextID presIdCmd,
    T_DIMSE_C_MoveRQ *request,
    DIMSE_MoveProviderCallback callback, void *callbackData,

    T_DIMSE_BlockingMode blockMode, int timeout)
{
    OFCondition cond = EC_Normal;
    T_ASC_PresentationContextID presIdData;
    DcmDataset *statusDetail = NULL;
    DcmDataset *reqIds = NULL;
    DcmDataset *rspIds = NULL;
    OFBool cancelled = OFFalse;
    OFBool normal = OFTrue;
    int responseCount = 0;
    T_DIMSE_C_MoveRSP rsp;

    cond = DIMSE_receiveDataSetInMemory(assoc, blockMode, timeout, &presIdData, &reqIds, NULL, NULL);

    if (cond.good()) {
        if (presIdData != presIdCmd) {
          cond = makeDcmnetCondition(DIMSEC_INVALIDPRESENTATIONCONTEXTID, OF_error, "DIMSE: Presentation Contexts of Command and Data Differ");
        } else {
            bzero((char*)&rsp, sizeof(rsp));
            rsp.DimseStatus = STATUS_Pending;

            while (cond == EC_Normal && rsp.DimseStatus == STATUS_Pending && normal) {
                responseCount++;

                cond = DIMSE_checkForCancelRQ(assoc, presIdCmd, request->MessageID);
                if (cond == EC_Normal) {

                    rsp.DimseStatus = STATUS_MOVE_Cancel_SubOperationsTerminatedDueToCancelIndication;
                    cancelled = OFTrue;
                } else if (cond == DIMSE_NODATAAVAILABLE) {

                } else {

                    normal = OFFalse;
                }

                if (normal) {
                     if (callback) {
                         callback(callbackData, cancelled, request, reqIds, responseCount, &rsp, &statusDetail, &rspIds);
                     } else {
                         return makeDcmnetCondition(DIMSEC_NULLKEY, OF_error, "DIMSE_moveProvider: no callback function");
                     }

                     if (cancelled) {

                         rsp.DimseStatus =
                           STATUS_MOVE_Cancel_SubOperationsTerminatedDueToCancelIndication;
                         if (rspIds != NULL) {
                             delete reqIds;
                             reqIds = NULL;
                         }
                     }

                     cond = DIMSE_sendMoveResponse(assoc, presIdCmd, request, &rsp, rspIds, statusDetail);

                     if (rspIds != NULL) {
                         delete rspIds;
                         rspIds = NULL;
                     }
                     if (statusDetail != NULL) {
                         delete statusDetail;
                         statusDetail = NULL;
                     }
                }
            }
        }
    }

    delete reqIds;
    delete rspIds;
    return cond;
}
