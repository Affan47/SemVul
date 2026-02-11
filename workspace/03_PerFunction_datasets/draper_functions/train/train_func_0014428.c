getResult() const {
  vector<vector<string> > result;
  for (vector<MBMAana>::const_iterator it=analysis.begin();
       it != analysis.end();
       it++ ){
    vector<string> mors = it->getMorph();
    if ( debugFlag ){
      *Log(mbmaLog) << "Morphs " << mors << endl;
    }
    result.push_back( mors );
  }
  if ( debugFlag ){
    *Log(mbmaLog) << "result of morph analyses: " << result << endl;
  }
  return result;
}
