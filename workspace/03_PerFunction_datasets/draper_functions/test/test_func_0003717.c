init( const Configuration& config ) {
  *Log(mblemLog) << "Initiating lemmatizer..." << endl;
  debug = tpDebug;
  string db = config.lookUp( "debug", "mblem" );
  if ( !db.empty() )
    debug = TiCC::stringTo<int>( db );
  string val = config.lookUp( "version", "mblem" );
  if ( val.empty() ){
    version = "1.0";
  }
  else
    version = val;
  val = config.lookUp( "set", "mblem" );
  if ( val.empty() ){
    tagset = "http://ilk.uvt.nl/folia/sets/frog-mblem-nl";
  }
  else
    tagset = val;

  val = config.lookUp( "set", "tagger" );
  if ( val.empty() ){
    cgn_tagset = "http://ilk.uvt.nl/folia/sets/frog-mbpos-cgn";
  }
  else
    cgn_tagset = val;

  string transName = config.lookUp( "transFile", "mblem" );
  if ( !transName.empty() ){
    transName = prefix( config.configDir(), transName );
    read_transtable( transName );
  }
  string treeName = config.lookUp( "treeFile", "mblem"  );
  if ( treeName.empty() )
    treeName = "mblem.tree";
  treeName = prefix( config.configDir(), treeName );
  string opts = config.lookUp( "timblOpts", "mblem" );
  if ( opts.empty() )
    opts = "-a1";

  opts += " +vs -vf";

  myLex = new Timbl::TimblAPI(opts);
  return myLex->GetInstanceBase(treeName);
}
