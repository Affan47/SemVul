Extract(long translationId, const string &dirNameStr)
  {
    const Moses::StaticData &staticData = Moses::StaticData::Instance();

    WordIndex wordIndex;

    string fuzzyMatchFile = ExtractTM(wordIndex, translationId, dirNameStr);


    create_xml(fuzzyMatchFile);


    string cmd;
    cmd = "LC_ALL=C sort " + fuzzyMatchFile + ".extract | gzip -c > "
    	+ fuzzyMatchFile + ".extract.sorted.gz";
    system(cmd.c_str());
    cmd = "LC_ALL=C sort " + fuzzyMatchFile + ".extract.inv | gzip -c > "
    	+ fuzzyMatchFile + ".extract.inv.sorted.gz";
    system(cmd.c_str());

#ifdef IS_XCODE
    cmd = "/Users/hieuhoang/unison/workspace/github/moses-smt/bin";
#elif IS_ECLIPSE
    cmd = "/home/hieu/workspace/github/moses-smt/bin";
#else
    cmd = staticData.GetBinDirectory();
#endif

    cmd += string("/../scripts/training/train-model.perl -dont-zip -first-step 6 -last-step 6 -f en -e fr -hierarchical ")
		    	+ " -extract-file " + fuzzyMatchFile + ".extract -lexical-file - -score-options \"--NoLex\" "
		    	+ " -phrase-translation-table " + fuzzyMatchFile + ".pt";
    system(cmd.c_str());


    return fuzzyMatchFile + ".pt.gz";
  }
