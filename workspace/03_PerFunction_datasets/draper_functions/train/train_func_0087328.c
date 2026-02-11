getSCP(T_ASC_Association * assoc, T_DIMSE_C_GetRQ * request,
        T_ASC_PresentationContextID presID, DcmQueryRetrieveDatabaseHandle& dbHandle)
{
    OFCondition cond = EC_Normal;
    DcmQueryRetrieveGetContext context(dbHandle, options_, STATUS_Pending, assoc, request->MessageID, request->Priority, presID);

    DIC_AE aeTitle;
    aeTitle[0] = '\0';
    ASC_getAPTitles(assoc->params, NULL, aeTitle, NULL);
    context.setOurAETitle(aeTitle);

    OFString temp_str;
    DCMQRDB_INFO("Received Get SCP:" << OFendl << DIMSE_dumpMessage(temp_str, *request, DIMSE_INCOMING));

    cond = DIMSE_getProvider(assoc, presID, request,
        getCallback, &context, options_.blockMode_, options_.dimse_timeout_);
    if (cond.bad()) {
        DCMQRDB_ERROR("Get SCP Failed: " << DimseCondition::dump(temp_str, cond));
    }
    return cond;
}
