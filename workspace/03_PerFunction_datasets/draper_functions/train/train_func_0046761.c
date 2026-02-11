GenerateFromUID(UIDs::TSName asname)
{
  PresContext.clear();

  const char *asnamestr = UIDs::GetUIDString( asname );
  const char *tsnamestr = GetDefaultTransferSyntax();


  if( asname == UIDs::PatientRootQueryRetrieveInformationModelMOVE )
    {
    const char *asnamestr0 = UIDs::GetUIDString(
      UIDs::PatientRootQueryRetrieveInformationModelFIND );
    AddPresentationContext( asnamestr0, tsnamestr );
    }
  else if( asname == UIDs::StudyRootQueryRetrieveInformationModelMOVE )
    {
    const char *asnamestr0 = UIDs::GetUIDString(
      UIDs::StudyRootQueryRetrieveInformationModelFIND );
    AddPresentationContext( asnamestr0, tsnamestr );
    }

  AddPresentationContext( asnamestr, tsnamestr );

  return true;
}
