DetermineMatchingKeyAttributeValues( DcmDataset *dataset, const char **&matchingKeyAttrValues )


{


  matchingKeyAttrValues = new const char*[ NUMBER_OF_SUPPORTED_MATCHING_KEY_ATTRIBUTES ];


  for( unsigned long i=0 ; i<NUMBER_OF_SUPPORTED_MATCHING_KEY_ATTRIBUTES ; i++ )
  {

    matchingKeyAttrValues[i] = NULL;


    DcmTagKey tag;
    switch( i )
    {
      case 0 : tag = DCM_ScheduledStationAETitle           ; break;
      case 1 : tag = DCM_ScheduledProcedureStepStartDate   ; break;
      case 2 : tag = DCM_ScheduledProcedureStepStartTime   ; break;
      case 3 : tag = DCM_Modality                          ; break;
      case 4 : tag = DCM_ScheduledPerformingPhysicianName  ; break;
      case 5 : tag = DCM_PatientName                       ; break;
      case 6 : tag = DCM_PatientID                         ; break;
      case 7 : tag = DCM_AccessionNumber                   ; break;
      case 8 : tag = DCM_RequestedProcedureID              ; break;
      case 9 : tag = DCM_ReferringPhysicianName            ; break;
      case 10 : tag = DCM_PatientSex                       ; break;
      case 11 : tag = DCM_RequestingPhysician              ; break;
      case 12 : tag = DCM_AdmissionID                      ; break;
      case 13 : tag = DCM_RequestedProcedurePriority       ; break;
      case 14 : tag = DCM_PatientBirthDate                 ; break;
      default:                                               break;
    }


    dataset->findAndGetString( tag, matchingKeyAttrValues[i], OFTrue );
  }
}
