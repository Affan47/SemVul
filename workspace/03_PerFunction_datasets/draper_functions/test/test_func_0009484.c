FinalPass()
{
  for( int level=highestLevel_; level>=0; --level )
  {
    std::vector<Workspace*> wsv;
    GetWorkspaces( level, wsv );
    std::vector<Workspace*>::const_iterator end( wsv.end() );
    for( std::vector<Workspace*>::const_iterator i(wsv.begin()); i!=end; ++i )
    {
      if( level==0 || ((*i)->IsRPNdone() && !(*i)->IsFinished()) )(*i)->Calculate();
    }
  }
  finalData_ = GetFinalWorkspace()->GetFinalData();
  type_ = NUMERIC;
}
