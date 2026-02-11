ConstructPDV(
 const ULConnection &inConnection, const BaseRootQuery* inRootQuery)
{
  std::vector<PresentationDataValue> thePDVs;
  PresentationDataValue thePDV;
#if 0
  int contextID = ePatientRootQueryRetrieveInformationModelFIND;
  const char *uid = UIDs::GetUIDString(
    UIDs::PatientRootQueryRetrieveInformationModelFIND );
  std::string suid = uid;
  if (dynamic_cast<const StudyRootQuery*>(inRootQuery)!=NULL)
    {
    contextID = eStudyRootQueryRetrieveInformationModelFIND;
    const char *uid2 = UIDs::GetUIDString(
      UIDs::StudyRootQueryRetrieveInformationModelFIND );
    suid = uid2;
    }
  thePDV.SetPresentationContextID(contextID);
#else
  PresentationContextRQ pc( inRootQuery->GetAbstractSyntaxUID() );
  uint8_t presidx = inConnection.GetPresentationContextIDFromPresentationContext(pc);
  if( !presidx )
    {

    PresentationContextRQ pc2( inRootQuery->GetAbstractSyntaxUID(), UIDs::ExplicitVRLittleEndian);
    presidx = inConnection.GetPresentationContextIDFromPresentationContext(pc2);
    if( !presidx )
      {
      gdcmErrorMacro( "Could not find Pres Cont ID" );
      return thePDVs;
      }
    }
  thePDV.SetPresentationContextID( presidx );
#endif

  thePDV.SetCommand(true);
  thePDV.SetLastFragment(true);


  CommandDataSet ds;
  ds.Insert( pc.GetAbstractSyntax().GetAsDataElement() );
  {
  Attribute<0x0,0x100> at = { 32 };
  ds.Insert( at.GetAsDataElement() );
  }
  {
  Attribute<0x0,0x110> at = { 1 };
  ds.Insert( at.GetAsDataElement() );
  }
  {
  Attribute<0x0,0x700> at = { 2 };
  ds.Insert( at.GetAsDataElement() );
  }
  {
  Attribute<0x0,0x800> at = { 1 };
  ds.Insert( at.GetAsDataElement() );
  }
  {
  Attribute<0x0,0x0> at = { 0 };
  unsigned int glen = ds.GetLength<ImplicitDataElement>();
  assert( (glen % 2) == 0 );
  at.SetValue( glen );
  ds.Insert( at.GetAsDataElement() );
  }

  thePDV.SetDataSet(ds);
  thePDVs.push_back(thePDV);
  thePDV.SetDataSet(inRootQuery->GetQueryDataSet());
  thePDV.SetMessageHeader( 2 );
  thePDVs.push_back(thePDV);
  return thePDVs;
}
