Defaults()
{
  nameTC_->Clear();
  minValueTC_->Clear();
  incValueTC_->Clear();
  maxValueTC_->Clear();
  numValueTC_->Clear();
  choicesRB_->SetSelection( 1 );
  SetUp();

  if( ExGlobals::StackIsOn() )ExGlobals::WriteStack( wxT("FORM GENERATE,DEFAULTS") );
}
