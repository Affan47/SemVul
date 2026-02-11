delAll( LineSequencer::Sequences& s)
{
  for ( Sequences::iterator i=s.begin(), e=s.end(); i!=e; ++i )
  {
    delete *i;
  }
}
