buildNCreateRSP(T_DIMSE_N_CreateRSP * e, DcmDataset * obj)
{
    OFCondition cond = buildCommonRSP(obj, DIMSE_N_CREATE_RSP,
        e->MessageIDBeingRespondedTo,
	e->DataSetType, e->DimseStatus); RET(cond);


    if (e->opts & O_NCREATE_AFFECTEDSOPCLASSUID) {
        cond = addString(obj, DCM_AffectedSOPClassUID,
            e->AffectedSOPClassUID, OFFalse); RET(cond);
    }
    if (e->opts & O_NCREATE_AFFECTEDSOPINSTANCEUID) {
        cond = addString(obj, DCM_AffectedSOPInstanceUID,
	    e->AffectedSOPInstanceUID, OFFalse); RET(cond);
    }
    return cond;
}
