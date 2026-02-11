reinitForAppending(){
  seq.v.erase( seq.v.begin(), seq.v.begin() + ends.v.back() - padSize );
  names.v.erase( names.v.begin(),
                 names.v.begin() + nameEnds.v[ finishedSequences() ] );
  ends.v.resize(1);
  nameEnds.v.resize(1);
  if( !names.v.empty() ) nameEnds.v.push_back( names.v.size() );
}
