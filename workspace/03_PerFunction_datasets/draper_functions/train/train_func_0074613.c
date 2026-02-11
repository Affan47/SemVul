DatasetIsComplete( DcmDataset *dataset )


{
  DcmElement *scheduledProcedureStepSequence = NULL;


  OFBool complete = OFTrue;

  DCMWLM_DEBUG("Checking whether dataset is complete ...");


  if( dataset->findAndGetElement( DCM_ScheduledProcedureStepSequence, scheduledProcedureStepSequence ).bad() || ((DcmSequenceOfItems*)scheduledProcedureStepSequence)->card() != 1 )
  {
    DCMWLM_DEBUG("- ScheduledProcedureStepSequence " << DCM_ScheduledProcedureStepSequence << " is missing or does not have exactly one item");
    complete = OFFalse;
  }
  else
  {


    DcmItem *scheduledProcedureStepSequenceItem = ((DcmSequenceOfItems*)scheduledProcedureStepSequence)->getItem(0);


    if( AttributeIsAbsentOrEmpty( DCM_ScheduledStationAETitle, scheduledProcedureStepSequenceItem ) ||
        AttributeIsAbsentOrEmpty( DCM_ScheduledProcedureStepStartDate, scheduledProcedureStepSequenceItem ) ||
        AttributeIsAbsentOrEmpty( DCM_ScheduledProcedureStepStartTime, scheduledProcedureStepSequenceItem ) ||
        AttributeIsAbsentOrEmpty( DCM_Modality, scheduledProcedureStepSequenceItem ) ||
        AttributeIsAbsentOrEmpty( DCM_ScheduledProcedureStepID, scheduledProcedureStepSequenceItem ) ||
        AttributeIsAbsentOrEmpty( DCM_RequestedProcedureID, dataset ) ||
        AttributeIsAbsentOrEmpty( DCM_StudyInstanceUID, dataset ) ||
        AttributeIsAbsentOrEmpty( DCM_PatientName, dataset ) ||
        AttributeIsAbsentOrEmpty( DCM_PatientID, dataset ) ||
        DescriptionAndCodeSequenceAttributesAreIncomplete( DCM_ScheduledProcedureStepDescription, DCM_ScheduledProtocolCodeSequence, scheduledProcedureStepSequenceItem ) ||
        DescriptionAndCodeSequenceAttributesAreIncomplete( DCM_RequestedProcedureDescription, DCM_RequestedProcedureCodeSequence, dataset ) ||
        ReferencedStudyOrPatientSequenceIsAbsentOrExistentButNonEmptyAndIncomplete( DCM_ReferencedStudySequence, dataset ) ||
        ReferencedStudyOrPatientSequenceIsAbsentOrExistentButNonEmptyAndIncomplete( DCM_ReferencedPatientSequence, dataset ) )
      complete = OFFalse;
  }

  return( complete );
}
