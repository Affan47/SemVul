saveImageToDB(
    T_DIMSE_C_StoreRQ *req,
    const char *imageFileName,

    T_DIMSE_C_StoreRSP *rsp,
    DcmDataset **stDetail)
{
    OFCondition dbcond = EC_Normal;
    DcmQueryRetrieveDatabaseStatus dbStatus(STATUS_Success);


    if (options_.ignoreStoreData_) {
        rsp->DimseStatus = STATUS_Success;
        *stDetail = NULL;
        return;
    }

    if (status == STATUS_Success)
    {
        dbcond = dbHandle.storeRequest(
            req->AffectedSOPClassUID, req->AffectedSOPInstanceUID,
            imageFileName, &dbStatus);
        if (dbcond.bad())
        {
            OFString temp_str;
            DCMQRDB_ERROR("storeSCP: Database: storeRequest Failed ("
                << DU_cstoreStatusString(dbStatus.status()) << "): "
                << DimseCondition::dump(temp_str, dbcond));
        }
        status = dbStatus.status();
    }

    rsp->DimseStatus = status;
    *stDetail = dbStatus.extractStatusDetail();
}
