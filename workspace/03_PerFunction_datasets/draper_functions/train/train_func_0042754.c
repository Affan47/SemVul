RefuseAssociation( T_ASC_Association **assoc, WlmRefuseReasonType reason )


{
  T_ASC_RejectParameters rej;


  switch( reason )
  {
    case WLM_TOO_MANY_ASSOCIATIONS: DCMWLM_INFO("Refusing Association (too many associations)"); break;
    case WLM_CANNOT_FORK:           DCMWLM_INFO("Refusing Association (cannot fork)"); break;
    case WLM_BAD_APP_CONTEXT:       DCMWLM_INFO("Refusing Association (bad application context)"); break;
    case WLM_BAD_AE_SERVICE:        DCMWLM_INFO("Refusing Association (bad application entity service)"); break;
    case WLM_FORCED:                DCMWLM_INFO("Refusing Association (forced via command line)"); break;
    case WLM_NO_IC_UID:             DCMWLM_INFO("Refusing Association (no implementation class UID provided)"); break;
    default:                        DCMWLM_INFO("Refusing Association (unknown reason)"); break;
  }


  switch( reason )
  {
    case WLM_TOO_MANY_ASSOCIATIONS:
      rej.result = ASC_RESULT_REJECTEDTRANSIENT;
      rej.source = ASC_SOURCE_SERVICEPROVIDER_PRESENTATION_RELATED;
      rej.reason = ASC_REASON_SP_PRES_LOCALLIMITEXCEEDED;
      break;
    case WLM_CANNOT_FORK:
      rej.result = ASC_RESULT_REJECTEDPERMANENT;
      rej.source = ASC_SOURCE_SERVICEPROVIDER_PRESENTATION_RELATED;
      rej.reason = ASC_REASON_SP_PRES_TEMPORARYCONGESTION;
      break;
    case WLM_BAD_APP_CONTEXT:
      rej.result = ASC_RESULT_REJECTEDTRANSIENT;
      rej.source = ASC_SOURCE_SERVICEUSER;
      rej.reason = ASC_REASON_SU_APPCONTEXTNAMENOTSUPPORTED;
      break;
    case WLM_BAD_AE_SERVICE:
      rej.result = ASC_RESULT_REJECTEDPERMANENT;
      rej.source = ASC_SOURCE_SERVICEUSER;
      rej.reason = ASC_REASON_SU_CALLEDAETITLENOTRECOGNIZED;
      break;
    case WLM_FORCED:
    case WLM_NO_IC_UID:
    default:
      rej.result = ASC_RESULT_REJECTEDPERMANENT;
      rej.source = ASC_SOURCE_SERVICEUSER;
      rej.reason = ASC_REASON_SU_NOREASON;
      break;
  }


  ASC_rejectAssociation( *assoc, &rej );


  ASC_dropAssociation( *assoc );


  ASC_destroyAssociation( assoc );
}
