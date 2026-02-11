retrieveStudyPatient(GATEWAY_EVENT * e, DUL_NETWORKKEY ** network,
	       DMAN_HANDLE ** d, FIS_HANDLE ** f, char *local, char *remote)
{
    CONDITION cond,
        rtnCond = 1;
    FIS_STUDYRECORD study;
    FIS_PATIENTRECORD patient;
    DUL_ASSOCIATESERVICEPARAMETERS params;
    DUL_ASSOCIATIONKEY *assoc;

    cond = requestAssociationHIS(d, local, remote, network, &assoc,
				 &params);
    if (cond != 1)
	return 0;

    cond = studyNGet(&assoc, &params, e->r.study.StuInsUID, &study);
    if (cond != 1)
	rtnCond = 0;

    if (rtnCond == 1) {
	cond = patientNGet(&assoc, &params, study.PatUID, &patient);
	if (cond != 1)
	    rtnCond = 0;
    }
    strcpy(patient.PatUID, study.PatUID);
    patient.Flag |= FIS_K_PAT_PATUID;
    (void) FIS_Delete(f, FIS_K_PATIENT, FIS_K_PATIENT, patient.PatUID);
    (void) FIS_Insert(f, FIS_K_PATIENT, &patient);

    strcpy(study.StuInsUID, e->r.study.StuInsUID);
    study.Flag |= FIS_K_STU_STUINSUID;
    (void) FIS_Delete(f, FIS_K_STUDY, FIS_K_STUDY, study.StuInsUID);
    (void) FIS_Insert(f, FIS_K_STUDY, &study);

    cond = releaseAssociation(&assoc, &params);
    if (cond != 1)
	rtnCond = 0;

    return rtnCond;
}
