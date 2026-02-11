AddGraphWindow( GRA_window *gw )
{
  int n = gw->GetNumber();
  int maxWindow = graphWindows_.size();
  if( n >= maxWindow )
  {
    int i = maxWindow-1;
    while( ++i < n )graphWindows_.push_back( new GRA_window(i) );
    graphWindows_.push_back( gw );
  }
  else
  {
    delete graphWindows_[n];
    graphWindows_[n] = gw;
  }
}
