CloseEventHandler( wxCloseEvent &WXUNUSED(event) )
{
  ExGlobals::DeleteStuff();


  wxConfigBase *config = wxConfigBase::Get();
  if( config )
  {
    int ulx, uly;
    GetPosition( &ulx, &uly );
    config->Write( wxT("/AnalysisWindow/UPPERLEFTX"), static_cast<long>(ulx) );
    config->Write( wxT("/AnalysisWindow/UPPERLEFTY"), static_cast<long>(uly) );
    int width, height;
    GetSize( &width, &height );
    config->Write( wxT("/AnalysisWindow/WIDTH"), static_cast<long>(width) );
    config->Write( wxT("/AnalysisWindow/HEIGHT"), static_cast<long>(height) );
  }
  Destroy();
}
