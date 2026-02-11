writeToFile(
    DcmFileFormat *ff,
    const char* fname,
    T_DIMSE_C_StoreRSP *rsp)
{
    E_TransferSyntax xfer = options_.writeTransferSyntax_;
    if (xfer == EXS_Unknown) xfer = ff->getDataset()->getOriginalXfer();

    OFCondition cond = ff->saveFile(fname, xfer, options_.sequenceType_,
        options_.groupLength_, options_.paddingType_, (Uint32)options_.filepad_,
        (Uint32)options_.itempad_, (options_.useMetaheader_) ? EWM_fileformat : EWM_dataset);

    if (cond.bad())
    {
      DCMQRDB_ERROR("storescp: Cannot write image file: " << fname);
      rsp->DimseStatus = STATUS_STORE_Refused_OutOfResources;
    }
}
