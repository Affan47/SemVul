BasicApplicationLevelConfidentialityProfile(bool deidentify)
{
  this->InvokeEvent( StartEvent() );
  bool ret;
  if( deidentify )
    ret = BasicApplicationLevelConfidentialityProfile1();
  else
    ret = BasicApplicationLevelConfidentialityProfile2();
  this->InvokeEvent( EndEvent() );
  return ret;
}
