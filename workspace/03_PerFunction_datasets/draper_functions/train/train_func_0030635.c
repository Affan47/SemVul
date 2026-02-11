load_corpus( const std::string &fileName, vector< vector< WORD_ID > > &corpus )
  {
    ifstream fileStream;
    fileStream.open(fileName.c_str());
    if (!fileStream) {
      cerr << "file not found: " << fileName << endl;
      exit(1);
    }
    cerr << "loading " << fileName << endl;

    istream *fileStreamP = &fileStream;

    char line[LINE_MAX_LENGTH];
    while(true)
    {
      SAFE_GETLINE((*fileStreamP), line, LINE_MAX_LENGTH, '\n');
      if (fileStreamP->eof()) break;
      corpus.push_back( GetVocabulary().Tokenize( line ) );
    }
  }
